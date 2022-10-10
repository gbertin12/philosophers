/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestamp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:44:19 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/08 20:05:10 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long 	get_timestamp()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	have_time(long long time, t_philo *philo)
{
	if (get_timestamp() - time > philo->general->time_to_die)
		return (1);
	return (0);
}

int	wait_activity(int time, t_philo *philo)
{
	long long start;

	start = get_timestamp();
	while(!have_time(start, philo) && !coroutine_to_die(philo))
	{
		if (get_timestamp() - start > time)
			return (0);
		usleep(50);
	}
	pthread_mutex_lock(philo->general->dead);
	philo->general->death = 1;
	pthread_mutex_unlock(philo->general->dead);
	return (1);
}
