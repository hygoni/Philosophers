/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:47:58 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/14 17:56:24 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "setting.h"
#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

t_data	g_data;

void	init(t_data *data)
{
	int					i;
	pthread_mutex_t		*mutex;

	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	data->mutex = mutex;
}

void	clear(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->mutex[i]);
		i++;
	}
	free(data->mutex);
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
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
		if (current_ms() - philo->last_eat_time >= (uint64_t)g_data.time_to_die)
		{
			ft_printf("%llu %d is died\n", current_ms(), philo->idx);
			exit(EXIT_FAILURE);
		}
		ft_printf("%llu %d is eating\n", current_ms(), philo->idx);		
		philo->last_eat_time = current_ms();
		usleep(g_data.time_to_eat);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		ft_printf("%llu %d is sleeping\n", current_ms(), philo->idx);
		usleep(g_data.time_to_sleep);
		ft_printf("%llu %d is thinking\n", current_ms(), philo->idx);
	}
	return (NULL);
}
