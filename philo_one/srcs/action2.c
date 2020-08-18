/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:21:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 18:21:54 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "ft.h"
#include "philo.h"
#include "setting.h"

extern		t_data	g_data;

void		stop_if_dead(void)
{
	pthread_mutex_lock(&g_data.dead);
	pthread_mutex_unlock(&g_data.dead);
}

int			is_eating_done(t_philo *philos)
{
	int			i;

	if (g_data.times_must_eat < 0)
		return (0);
	i = 0;
	while (i < g_data.size)
	{
		if (philos[i].count > 0)
			return (0);
		i++;
	}
	return (1);
}

void		*monitor(void *ptr)
{
	int			i;
	t_philo		*philos;
	uint64_t		diff;

	philos = (t_philo*)ptr;
	while (1)
	{
		i = 0;
		while (i < g_data.size)
		{
			diff = current_ms() - philos[i].last_eat_time;
			if (diff >= (uint64_t)g_data.time_to_die)
			{
				print(&g_data.io_lock, current_ms() - g_data.start, \
						philos[i].idx, "died");
				pthread_mutex_lock(&g_data.dead);
				return (NULL);
			}
			if (is_eating_done(philos))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
