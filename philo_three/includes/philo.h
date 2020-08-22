/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:59:38 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/22 13:59:03 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "setting.h"

int			init(t_data *data);
int			clear(t_data *data);
void		*monitor(void *ptr);
void		*philosopher(void *ptr);
uint64_t	current_ms();
void		do_eat(t_philo *philo);
void		do_sleep(t_philo *philo);
void		do_think(t_philo *philo);
int			is_died(t_philo *philo);
void		lock(t_philo *philo);
void		unlock();
void		stop_if_dead();
void		ft_sleep(int ms);

#endif
