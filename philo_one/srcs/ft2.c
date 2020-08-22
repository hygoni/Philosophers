/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 01:37:08 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/22 14:01:17 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "philo.h"
#include <stdint.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int		sign;
	long	num;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	num = 0;
	while ('0' <= *str && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return ((int)num * sign);
}

void	ft_sleep(int ms)
{
	uint64_t	start;

	start = current_ms();
	while (current_ms() - start < (uint64_t)ms)
	{
		usleep(500);
	}
	return ;
}
