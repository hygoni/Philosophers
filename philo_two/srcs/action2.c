/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:21:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/22 18:52:19 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft.h"
#include "philo.h"
#include "setting.h"
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

extern		t_data	g_data;

void		stop_if_dead(void)
{
	sem_wait(g_data.dead_lock);
	sem_post(g_data.dead_lock);
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
		if (philos[i].count == 0 && !philos[i].is_stopped)
			return (0);
		i++;
	}
	return (1);
}

void		*monitor(void *ptr)
{
	int			i;
	t_philo		*philos;

	philos = (t_philo*)ptr;
	while (1)
	{
		i = 0;
		while (i < g_data.size)
		{
			if (current_ms() - philos[i].last_eat_time >= \
			(uint64_t)g_data.time_to_die && !philos[i].is_stopped)
			{
				sem_wait(g_data.dead_lock);
				print_no_deadcheck(g_data.io_lock, \
					current_ms() - g_data.start, philos[i].idx, "died");
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
