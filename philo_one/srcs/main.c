/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:27:38 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/14 17:21:04 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "setting.h"
#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

t_data		g_data;

int		parse(t_data *data, int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (0);
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = -1;
	return (1);
}

int		main(int argc, char **argv)
{
	int		i;

	if (!parse(&g_data, argc, argv))
	{
		ft_putstr("Argument Error\n");
		return (1);
	}
	init(&g_data);
	t_philo *philosophers = (t_philo*)malloc(sizeof(t_philo) * g_data.number_of_philo);
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * g_data.number_of_philo);
	i = 0;
	while (i < g_data.number_of_philo)
	{
		philosophers[i].idx = i;
		philosophers[i].last_eat_time = current_ms();
		if (i == g_data.number_of_philo - 1)
		{
			philosophers[i].left = &g_data.mutex[0];
			philosophers[i].right = &g_data.mutex[i];
		}
		else
		{
			philosophers[i].left = &g_data.mutex[i];
			philosophers[i].right = &g_data.mutex[i + 1];
		}
		pthread_create(&threads[i], NULL, philosopher, &philosophers[i]);
		i++;
	}
	i = 0;
	while (i < g_data.number_of_philo)
		pthread_join(threads[i++], NULL);
	free(philosophers);
	clear(&g_data);
	return (0);
}
