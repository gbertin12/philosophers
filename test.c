/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:59:29 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/11 20:23:55 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int main()
{
	struct timeval	tv;
	struct timeval tv2;

	gettimeofday(&tv, NULL);
	usleep(100000);
	gettimeofday(&tv2, NULL);
	printf("%ld sec %ld  usec %d\n", (tv.tv_sec * 1000000) + tv.tv_usec, tv.tv_sec, tv.tv_usec);
	printf("%ld sec %ld  usec %d\n", (tv2.tv_sec * 1000000) + tv2.tv_usec, tv2.tv_sec, tv2.tv_usec);
	printf("diff without div = %ld\n",((tv2.tv_sec * 1000000) + tv2.tv_usec) - ((tv.tv_sec * 1000000) + tv.tv_usec));
	printf("diff with div = %ld\n",((tv2.tv_sec * 1000000) + tv2.tv_usec) - ((tv.tv_sec * 1000000) + tv.tv_usec));
	printf("diff usec = %d\n",tv2.tv_usec - tv.tv_usec);
	return (0);
}