/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:47:58 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/22 18:19:25 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "setting.h"
#include "ft.h"
#include <fcntl.h>
#include <unistd.h>
#include "philo.h"
#include <sys/wait.h>

extern t_data	g_data;

void			*monitor_starvation(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo*)ptr;
	while (1)
	{
		if (current_ms() - philo->last_eat_time >= \
			(uint64_t)g_data.time_to_die && !philo->is_stopped)
		{
			print(g_data.io_lock, current_ms() - g_data.start, \
					philo->idx, "died");
			sem_wait(g_data.dead_lock);
			exit(EXIT_FAILURE);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int				init(t_data *data)
{
	int	max_eating;
	int	forks;
	int	n;

	n = data->number_of_philo;
	forks = (n == 1) ? 2 : n;
	if (forks % 2 == 0)
		max_eating = (forks / 2);
	else
		max_eating = (forks - 1) / 2;
	sem_unlink("eat_lock");
	sem_unlink("fork_lock");
	sem_unlink("io_lock");
	sem_unlink("dead_lock");
	data->eat_lock = sem_open("eat_lock", O_CREAT, 0644, max_eating);
	data->fork_lock = sem_open("fork_lock", O_CREAT, 0644, forks);
	data->io_lock = sem_open("io_lock", O_CREAT, 0644, 1);
	data->dead_lock = sem_open("dead_lock", O_CREAT, 0644, 1);
	data->pid = (pid_t*)malloc(sizeof(pid_t) * (n + 1));
	if (!data->eat_lock || !data->fork_lock || !data->io_lock
			|| !data->pid || !data->dead_lock)
		return (-1);
	return (0);
}

int				clear(t_data *data)
{
	sem_unlink("eat_lock");
	sem_unlink("fork_lock");
	sem_unlink("io_lock");
	sem_unlink("dead_lock");
	free(data->pid);
	return (0);
}

uint64_t		current_ms(void)
{
	struct timeval	time;
	uint64_t		millis;

	gettimeofday(&time, NULL);
	millis = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
	return (millis);
}

void			*philosopher(void *ptr)
{
	t_philo		*philo;
	int			count;
	pthread_t	thread;

	philo = (t_philo*)ptr;
	count = g_data.times_must_eat;
	pthread_create(&thread, NULL, monitor_starvation, philo);
	pthread_detach(thread);
	philo->is_stopped = 0;
	while (count-- || g_data.times_must_eat < 0)
	{
		lock(philo);
		do_eat(philo);
		unlock();
		do_sleep(philo);
		do_think(philo);
	}
	philo->is_stopped = 1;
	return (NULL);
}
