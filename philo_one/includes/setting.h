/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:39:16 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/16 01:42:06 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

# include <pthread.h>
# include <sys/time.h>

typedef struct		s_data
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_must_eat;
	int					philo_idx;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		*io_lock;
}		t_data;

typedef struct		s_philo
{
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	int			idx;
	uint64_t		last_eat_time;
}		t_philo;

#endif
