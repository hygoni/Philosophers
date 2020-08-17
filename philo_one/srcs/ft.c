/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 01:26:33 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/17 13:01:29 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
		len++;
	write(1, str, len);
}

void	ft_putnbr(uint64_t n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n / 10 != 0)
			ft_putnbr(-(n / 10));
		ft_putchar(-(n % 10) + '0');
	}
	else
	{
		if (n >= 10)
			ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
}

void	print(pthread_mutex_t *lock, uint64_t time, int number, char *action)
{
	pthread_mutex_lock(lock);
	ft_putnbr(time);
	ft_putchar(' ');
	ft_putnbr(number);
	ft_putchar(' ');
	ft_putstr(action);
	ft_putchar('\n');
	pthread_mutex_unlock(lock);
}
