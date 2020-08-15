/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:21:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/16 05:27:05 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "philo.h"
#include "setting.h"

extern		int	g_died;
extern		t_data	g_data;

int		is_died(t_philo *philo)
{
	if (current_ms() - philo->last_eat_time >= (uint64_t)g_data.time_to_die)
	{
		print(&g_data.io_lock, current_ms(), philo->idx, "died");
		g_died = 1;
		unlock(philo);
		return (-1);
	}
	return (0);
}
