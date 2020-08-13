/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:47:58 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/14 08:55:40 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include ""
void	init(t_data *data)
{
	int					i;
	pthread_mutex_t		*mutex;

	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&mutex[i]);
		i++;
	}
	data->mutex = mutex;
}

void	clear(t_data *data)
{
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(data->mutex[i]);
		i++;
	}
	free(data->mutex);
}

void	*philosopher(void *ptr)
{
	t_data *data;
	int			count;

	data = (t_data*)ptr;
	while (count < data->nu)
}
