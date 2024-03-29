/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 21:59:31 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/22 18:21:23 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "setting.h"
#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

extern		t_data	g_data;

void			*monitor(void *ptr)
{
	pid_t	child;
	int		status;
	int		i;
	t_philo	*philo;

	philo = (t_philo*)ptr;
	child = fork();
	if (child == 0)
	{
		philosopher(ptr);
		exit(EXIT_SUCCESS);
	}
	waitpid(g_data.pid[philo->idx] = child, &status, 0);
	if (WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		i = 0;
		while (i < g_data.number_of_philo)
		{
			if (g_data.pid[i] != child)
				kill(g_data.pid[i], SIGINT);
			i++;
		}
	}
	return (NULL);
}
