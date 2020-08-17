/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 01:26:33 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/17 13:31:29 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <semaphore.h>

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

void	print(sem_t *lock, uint64_t timestamp, int philo_number, char *action)
{
	sem_wait(lock);
	ft_putnbr(timestamp);
	ft_putchar(' ');
	ft_putnbr(philo_number);
	ft_putchar(' ');
	ft_putstr(action);
	ft_putchar('\n');
	sem_post(lock);
}
