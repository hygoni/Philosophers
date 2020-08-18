/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:21:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 00:49:15 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft.h"
#include "philo.h"
#include "setting.h"

extern		int	g_died;
extern		t_data	g_data;

int		is_dead(pthread_mutex_t *dead)
{
	if (pthread_mutex_unlock(dead) == 0)
	{
		pthread_mutex_lock(dead);
		return (1);
	}
	else
		return (0);
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

			if (current_ms() - philos[i].last_eat_time 
					>= (uint64_t)g_data.time_to_die)
			{
				print(&g_data.io_lock, current_ms() - g_data.start, \
						philos[i].idx, "died");
				pthread_mutex_lock(&g_data.dead);
				return (NULL);
			}
			usleep(1000);
		}
	}
	return (NULL);
}
