/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestamp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:44:19 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/13 11:30:25 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		perror("");
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	wait_eat(int time, t_philo *philo)
{
	long long	start;

	start = get_timestamp();
	while (!check_death(philo))
	{
		if (get_timestamp() - start > time)
			return (0);
		usleep(20);
	}
	return (1);
}

int	wait_sleep(int time, t_philo *philo)
{
	long long	start;

	start = get_timestamp();
	while (!check_death(philo) && !coroutine_to_die(philo))
	{
		if (get_timestamp() - start > time)
			return (0);
		usleep(20);
	}
	return (1);
}
