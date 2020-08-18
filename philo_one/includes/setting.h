/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:39:16 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 22:07:20 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct			s_data
{
	int					size;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_must_eat;
	int					philo_idx;
	uint64_t			start;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		dead;
	pthread_mutex_t		exit;
	pthread_mutex_t		io_lock;
}						t_data;

typedef struct			s_philo
{
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	int					idx;
	int					count;
	uint64_t			last_eat_time;
}						t_philo;

#endif
