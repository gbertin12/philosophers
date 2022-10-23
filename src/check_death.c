/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:53:00 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/23 07:44:02 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->general->dead);
	if (philo->general->death == 1)
	{
		pthread_mutex_unlock(&philo->general->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->general->dead);
	return (0);
}

int	coroutine_to_die(t_philo *philo)
{
	long long	duration;

	duration = get_timestamp() - philo->last_eat;
	if (duration > philo->general->time_to_die)
	{
		print_msg("died", philo);
		pthread_mutex_lock(&philo->general->dead);
		philo->general->death = 1;
		pthread_mutex_unlock(&philo->general->dead);
		return (1);
	}
	return (0);
}
