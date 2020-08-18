/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:47:58 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/19 01:45:38 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "setting.h"
#include "ft.h"
#include <fcntl.h>
#include <unistd.h>
#include "philo.h"

extern t_data	g_data;

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
	if (!data->eat_lock || !data->fork_lock ||
			!data->io_lock || !data->dead_lock)
		return (-1);
	return (0);
}

int				clear(t_data *data)
{
	sem_close(data->eat_lock);
	sem_close(data->fork_lock);
	sem_close(data->io_lock);
	sem_close(data->dead_lock);
	sem_unlink("eat_lock");
	sem_unlink("fork_lock");
	sem_unlink("io_lock");
	sem_unlink("dead_lock");
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
	t_philo	*philo;

	philo = (t_philo*)ptr;
	philo->count = g_data.times_must_eat;
	philo->is_stopped = 0;
	while (philo->count > 0 || g_data.times_must_eat < 0)
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
