/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:47:58 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/16 02:25:44 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "setting.h"
#include "ft.h"
#include <unistd.h>
extern int	g_died;
extern t_data	g_data;

int	init(t_data *data)
{
	int					i;
	pthread_mutex_t		*mutex;

	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (mutex == NULL)
		return (-1);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_init(&mutex[i], NULL) == -1)
			return (-1);
		i++;
	}
	data->mutex = mutex;
	if (pthread_mutex_init(&data->io_lock, NULL) == -1)
		return (-1);
	return (0);
}

int	clear(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_mutex_destroy(&data->mutex[i]) == -1)
			return (-1);
		i++;
	}
	free(data->mutex);
	if (pthread_mutex_destroy(&data->io_lock) == -1)
		return (-1);
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
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
		if (current_ms() - philo->last_eat_time >= (uint64_t)g_data.time_to_die)
		{
			print(&g_data.io_lock, current_ms(), philo->idx, "died");
			g_died = 1;
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(philo->left);
			return (NULL);
		}
		print(&g_data.io_lock, current_ms(), philo->idx, "eating");	
		usleep(g_data.time_to_eat * 1000);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		philo->last_eat_time = current_ms();
		print(&g_data.io_lock, current_ms(), philo->idx, "sleeping");
		usleep(g_data.time_to_sleep * 1000);
		print(&g_data.io_lock, current_ms(), philo->idx, "thinking");
	}
	return (NULL);
}
