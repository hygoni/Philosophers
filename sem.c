/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 12:50:47 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/19 18:55:55 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem.h"
#include <pthread.h>
#include <unistd.h>

int		init_sem(t_sem *sem, int num)
{
	if (pthread_mutex_init(&sem->edit, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&sem->wait, NULL) == -1)
		return (-1);
	sem->num = num;
	sem->value = 0;
	return (0);
}

int		destroy_sem(t_sem *sem)
{
	if (pthread_mutex_destroy(&sem->edit) == -1)
		return (-1);
	if (pthread_mutex_destroy(&sem->wait) == -1)
		return (-1);
	return (0);
}

void		wait_sem(t_sem *sem)
{
	pthread_mutex_lock(&sem->edit);
	if (sem->num - sem->value > 0)
	{
		sem->value++;
		pthread_mutex_unlock(&sem->edit);
		return ;
	}
	else
	{

		pthread_mutex_unlock(&sem->edit);
		while (1)
		{
			pthread_mutex_lock(&sem->edit);
			if (sem->num - sem->value > 0)
			{
				sem->value++;
				pthread_mutex_unlock(&sem->edit);
				return ;
			}
			pthread_mutex_unlock(&sem->edit);
			usleep(100);
		}
				
	}

}

void		post_sem(t_sem *sem)
{
	pthread_mutex_lock(&sem->edit);
	sem->value--;
	pthread_mutex_unlock(&sem->edit);
}
