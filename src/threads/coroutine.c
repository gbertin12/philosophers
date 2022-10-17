/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coroutine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:47:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/17 18:30:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	coroutine_to_die(t_philo *philo)
{
	int	duration;

	duration = get_timestamp() - philo->last_eat;
	if (duration >= philo->general->time_to_die)
	{
		print_msg("died", philo);
		pthread_mutex_lock(&philo->general->dead);
		philo->general->death = 1;
		pthread_mutex_unlock(&philo->general->dead);
		return (1);
	}
	return (0);
}

int	coroutine_take_forks(t_philo *philo)
{
	if (lock_fork_right(philo))
		return (1);
	print_msg("has taken a fork", philo);
	if (!philo->fork_left)
	{
		pthread_mutex_unlock(&philo->fork_right->fork);
		wait_action(philo->general->time_to_die, philo);
		return (1);
	}
	if (lock_fork_left(philo))
	{
		unlock_fork_right(philo);
		return (1);
	}
	print_msg("has taken a fork", philo);
	if (coroutine_to_die(philo))
	{
		unlock_fork_left(philo);
		unlock_fork_right(philo);
		return (1);
	}
	return (0);
}

int	coroutine_to_eat(t_philo *philo)
{
	print_msg("is eating", philo);
	philo->last_eat = get_timestamp();
	if (wait_action(philo->general->time_to_eat, philo))
	{
		unlock_fork_left(philo);
		unlock_fork_right(philo);
		return (1);
	}
	unlock_fork_left(philo);
	unlock_fork_right(philo);
	return (0);
}

int	coroutine_to_sleep(t_philo *philo)
{
	print_msg("is sleeping", philo);
	if (wait_action(philo->general->time_to_sleep, philo))
		return (1);
	print_msg("is thinking", philo);
	usleep(100);
	return (0);
}
