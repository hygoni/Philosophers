/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:16:30 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/16 05:26:03 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "setting.h"
#include "philo.h"
#include <unistd.h>

extern	t_data g_data;

void	lock(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->left);
}

void	unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	do_eat(t_philo *philo)
{
	print(&g_data.io_lock, current_ms(), philo->idx, "eating");
	usleep(g_data.time_to_eat * 1000);
	philo->last_eat_time = current_ms();
}

void	do_sleep(t_philo *philo)
{
	print(&g_data.io_lock, current_ms(), philo->idx, "sleeping");
	usleep(g_data.time_to_sleep * 1000);
}

void	do_think(t_philo *philo)
{
	print(&g_data.io_lock, current_ms(), philo->idx, "thinking");
}
