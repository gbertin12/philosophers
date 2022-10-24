/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:53:00 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/24 15:57:04 by gbertin          ###   ########.fr       */
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
		print_msg("died\n", philo);
		pthread_mutex_lock(&philo->general->dead);
		philo->general->death = 1;
		pthread_mutex_unlock(&philo->general->dead);
		return (1);
	}
	return (0);
}
