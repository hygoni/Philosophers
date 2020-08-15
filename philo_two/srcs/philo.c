/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:47:58 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/16 03:02:02 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "setting.h"
#include "ft.h"
#include <fcntl.h>
#include <unistd.h>
extern int	g_died;
extern t_data	g_data;

int	init(t_data *data)
{
	int	max_eating;
	int	forks;
	int	n;

	n = data->number_of_philo;
	forks = (n == 1) ? 2 : n;
	if (forks % 2 == 0)
	{
		max_eating = (forks / 2);
	}
	else
	{
		max_eating = (forks - 1) / 2;
	}
	data->eat_lock = sem_open("eat_lock", O_CREAT, 0644, max_eating);
	data->fork_lock = sem_open("fork_lock", O_CREAT, 0644, forks);
	data->io_lock = sem_open("io_lock", O_CREAT, 0644, 1);
	if (!data->eat_lock || !data->fork_lock || !data->io_lock)
		return (-1);
	return (0);
}

int	clear(t_data *data)
{
	sem_close(data->eat_lock);
	sem_close(data->fork_lock);
	sem_close(data->io_lock);
	sem_unlink("eat_lock");
	sem_unlink("fork_lock");
	sem_unlink("io_lock");
	return (0);
}

uint64_t	current_ms()
{
	struct timeval time;
	uint64_t millis;

	gettimeofday(&time, NULL);
	millis = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
	return (millis);
}

void	*philosopher(void *ptr)
{
	t_philo *philo;
	int	count;

	philo = (t_philo*)ptr;
	count = g_data.times_must_eat;
	while (count-- || g_data.times_must_eat < 0)
	{
		if (g_died)
			return (NULL);
		sem_wait(g_data.eat_lock);
		sem_wait(g_data.fork_lock);
		sem_wait(g_data.fork_lock);
		if (current_ms() - philo->last_eat_time >= (uint64_t)g_data.time_to_die)
		{
			print(g_data.io_lock, current_ms(), philo->idx, "died");
			g_died = 1;
			sem_post(g_data.fork_lock);
			sem_post(g_data.fork_lock);
			sem_post(g_data.eat_lock);
			return (NULL);
		}
		print(g_data.io_lock, current_ms(), philo->idx, "eating");	
		usleep(g_data.time_to_eat * 1000);
		sem_post(g_data.fork_lock);
		sem_post(g_data.fork_lock);
		sem_post(g_data.eat_lock);
		philo->last_eat_time = current_ms();
		print(g_data.io_lock, current_ms(), philo->idx, "sleeping");
		usleep(g_data.time_to_sleep * 1000);
		print(g_data.io_lock, current_ms(), philo->idx, "thinking");
	}
	return (NULL);
}
