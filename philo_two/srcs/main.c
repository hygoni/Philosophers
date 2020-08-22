/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:27:38 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/20 01:08:49 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "setting.h"
#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_data		g_data;
int			g_died = 0;

int		parse(t_data *data, int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (-1);
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = -1;
	return (0);
}

int		error_ret(char *msg, int ret)
{
	ft_putstr(msg);
	return (ret);
}

int		run_philo(t_philo **philos_out, pthread_t **threads_out)
{
	int			i;
	t_philo		*philos;
	pthread_t	*threads;

	g_data.size = g_data.number_of_philo;
	philos = (t_philo*)malloc(sizeof(t_philo) * g_data.size);
	threads = (pthread_t*)malloc(sizeof(pthread_t) * (g_data.size + 1));
	if (philos == NULL || threads == NULL)
		return (error_ret("Error\n", 1));
	g_data.start = current_ms();
	i = 1;
	while (i < g_data.number_of_philo)
	{
		philos[i].idx = i + 1;
		philos[i].last_eat_time = current_ms();
		pthread_create(&threads[i], NULL, philosopher, &philos[i]);
		i += 2;
	}
	usleep(g_data.time_to_eat * 1000);
	i = 0;
	while (i < g_data.number_of_philo)
	{
		philos[i].idx = i + 1;
		philos[i].last_eat_time = current_ms();
		pthread_create(&threads[i], NULL, philosopher, &philos[i]);
		i += 2;
	}
	pthread_create(&threads[g_data.size], NULL, monitor, philos);
	*philos_out = philos;
	*threads_out = threads;
	i = 0;
	while (i < g_data.number_of_philo)
		pthread_detach(threads[i++]);
	pthread_join(threads[g_data.size], NULL);
	return (0);
}

int		main(int argc, char **argv)
{
	pthread_t	*threads;
	t_philo		*philos;

	if (parse(&g_data, argc, argv) == -1)
		return (error_ret("Argument Error\n", 1));
	else if (init(&g_data) == -1)
		return (error_ret("Error\n", 1));
	else if (run_philo(&philos, &threads) == -1)
		return (error_ret("Error\n", 1));
	usleep(1000);
	if (clear(&g_data) == -1)
		return (error_ret("Error\n", 1));
	free(philos);
	free(threads);
	return (0);
}
