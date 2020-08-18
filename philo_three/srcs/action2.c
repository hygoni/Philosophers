/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:21:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 18:34:30 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "philo.h"
#include "setting.h"

extern		t_data	g_data;

int		is_died(t_philo *philo)
{
	if (current_ms() - philo->last_eat_time >= (uint64_t)g_data.time_to_die)
	{
		sem_wait(g_data.dead_lock);
		print(g_data.io_lock, current_ms() - g_data.start, philo->idx, "died");
		unlock();
		return (-1);
	}
	return (0);
}

void		stop_if_dead(void)
{
	sem_wait(g_data.dead_lock);
	sem_post(g_data.dead_lock);
}
