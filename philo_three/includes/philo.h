/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:59:38 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/16 04:49:29 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

int	init(t_data *data);
int	clear(t_data *data);
void	*monitor(void *ptr);
void	*philosopher(void *ptr);
uint64_t	current_ms();

#endif
