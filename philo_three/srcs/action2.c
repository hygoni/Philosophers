/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 05:21:49 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 21:58:14 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "philo.h"
#include "setting.h"

extern		t_data	g_data;

void		stop_if_dead(void)
{
	sem_wait(g_data.dead_lock);
	sem_post(g_data.dead_lock);
}
