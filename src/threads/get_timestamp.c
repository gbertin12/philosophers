/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestamp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:44:19 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/17 23:24:34 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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

int	wait_action(int time, t_philo *philo)
{
	long long	start;
	long long	next_death;

	start = get_timestamp();
	next_death = philo->general->time_to_die - (get_timestamp() - philo->last_eat);
	// printf("timestamp %lld  last eat %lld\n", get_timestamp(), philo->last_eat);
	// printf("next death = %lld || end action %d soustraction %lld\n", next_death, time, next_death - philo->general->time_to_die);
	//printf("next death %lld time to die %d\n", next_death, philo->general->time_to_die);
	if (next_death < time)
	{
		while (!check_death(philo) && !coroutine_to_die(philo))
		{
			if (get_timestamp() - start > time)
				return (0);
			usleep(500);
		}
		return (1);
	}
	else
	{
		usleep(time * 1000);
		return (0);
	}
	return (1);
}

void	init_start(t_philo *philo)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	philo->general->time_start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (philo->general->time_start % 1000 != 0)
	{
		philo->general->time_start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		gettimeofday(&time, NULL);
	}
}
