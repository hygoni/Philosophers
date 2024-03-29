/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:59:38 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 15:26:53 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "setting.h"

int			init(t_data *data);
int			clear(t_data *data);
void		*philosopher(void *ptr);
uint64_t	current_ms();
void		do_eat(t_philo *philo);
void		do_sleep(t_philo *philo);
void		do_think(t_philo *philo);
int			is_died(t_philo *philo);
void		lock(t_philo *philo);
void		unlock(t_philo *philo);
void		stop_if_dead();
void		*monitor(void *philos);
void		*monitor_eat(void *ptr);

#endif
