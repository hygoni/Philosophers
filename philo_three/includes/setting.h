/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:39:16 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 18:29:32 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

# include <stdint.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct		s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				*pid;
	uint64_t			start;
	sem_t			*eat_lock;
	sem_t			*fork_lock;
	sem_t			*dead_lock;
	sem_t			*io_lock;
}					t_data;

typedef struct		s_philo
{
	int				idx;
	uint64_t		last_eat_time;
}					t_philo;

#endif
