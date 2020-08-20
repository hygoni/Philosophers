/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:16:30 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/20 19:26:17 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "setting.h"
#include "philo.h"
#include <unistd.h>

extern	t_data g_data;

void	lock(t_philo *philo)
{
	pthread_mutex_lock(&g_data.pickup);
	pthread_mutex_lock(philo->left);
	print(&g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "has taken a fork");
	pthread_mutex_lock(philo->right);
	print(&g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "has taken a fork");
	pthread_mutex_unlock(&g_data.pickup);
}

void	unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	do_eat(t_philo *philo)
{
	print(&g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "is eating");
	philo->last_eat_time = current_ms();
	if (g_data.times_must_eat >= 0)
		philo->count--;
	usleep(g_data.time_to_eat * 1000);
}

void	do_sleep(t_philo *philo)
{
	print(&g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "is sleeping");
	usleep(g_data.time_to_sleep * 1000);
}

void	do_think(t_philo *philo)
{
	print(&g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "is thinking");
}
