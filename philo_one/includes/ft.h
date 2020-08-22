/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 01:34:46 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/22 17:36:53 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <stdint.h>
# include <pthread.h>

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(uint64_t n);
void	ft_sleep(int ms);
int		ft_atoi(char *str);
void	print(pthread_mutex_t *lock, uint64_t time, int number, char *msg);
int		error_ret(char *msg, int ret);

#endif
