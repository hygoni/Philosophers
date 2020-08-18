/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyoo <hyeyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 01:02:24 by hyeyoo            #+#    #+#             */
/*   Updated: 2020/08/18 02:21:55 by hyeyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

int		main(void)
{
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);
	int ret = pthread_mutex_unlock(&mutex);
	printf("%d\n", ret);
}
