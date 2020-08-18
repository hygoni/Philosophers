/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:59:38 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 22:05:06 by hyeyoo           ###   ########.fr       */
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
void		lock(t_philo *philo);
void		unlock();
void		stop_if_dead(void);
void		*monitor(void *ptr);

#endif
