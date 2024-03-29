/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:47:58 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/22 17:39:07 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "setting.h"
#include "ft.h"
#include "philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

extern int	g_died;
extern t_data	g_data;

int				init(t_data *data)
{
	int					i;

	data->mutex = \
		(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * data->size);
	if (data->mutex == NULL)
		return (-1);
	i = 0;
	while (i < data->size)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL) == -1)
			return (-1);
		i++;
	}
	data->start = current_ms();
	if (pthread_mutex_init(&data->io_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&data->dead, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&data->pickup, NULL) == -1)
		return (-1);
	return (0);
}

int				clear(t_data *data)
{
	int i;

	i = 0;
	while (i < data->size)
	{
		if (pthread_mutex_destroy(&data->mutex[i]) == -1)
			return (-1);
		i++;
	}
	free(data->mutex);
	if (pthread_mutex_destroy(&data->io_lock) == -1)
		return (-1);
	if (pthread_mutex_destroy(&data->dead) == -1)
		return (-1);
	if (pthread_mutex_destroy(&data->pickup) == -1)
		return (-1);
	return (0);
}

uint64_t		current_ms(void)
{
	struct timeval		time;
	uint64_t			millis;

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
		unlock(philo);
		do_sleep(philo);
		do_think(philo);
	}
	philo->is_stopped = 1;
	return (NULL);
}
