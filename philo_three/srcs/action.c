/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:16:30 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/22 13:59:40 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "setting.h"
#include "philo.h"
#include <unistd.h>

extern	t_data g_data;

void	lock(t_philo *philo)
{
	sem_wait(g_data.eat_lock);
	sem_wait(g_data.fork_lock);
	sem_wait(g_data.fork_lock);
	print(g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "has taken a fork");
	print(g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "has taken a fork");
}

void	unlock(void)
{
	sem_post(g_data.eat_lock);
	sem_post(g_data.fork_lock);
	sem_post(g_data.fork_lock);
}

void	do_eat(t_philo *philo)
{
	print(g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "is eating");
	philo->last_eat_time = current_ms();
	ft_sleep(g_data.time_to_eat);
}

void	do_sleep(t_philo *philo)
{
	print(g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "is sleeping");
	ft_sleep(g_data.time_to_sleep);
}

void	do_think(t_philo *philo)
{
	print(g_data.io_lock, current_ms() - g_data.start, \
			philo->idx, "is thinking");
}
