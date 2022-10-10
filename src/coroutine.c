/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coroutine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:47:27 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/08 20:10:12 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->general->write);
	printf("%lldms p%d %s\n", get_timestamp(philo) - philo->general->time_start, philo->num_philo, msg);
	pthread_mutex_unlock(philo->general->write);
}

int	coroutine_to_die(t_philo *philo)
{
	int duration;

	duration = get_timestamp() - philo->last_eat;
	if (duration > philo->general->time_to_die)
	{
		pthread_mutex_lock(philo->general->dead);
		philo->general->death = 1;
		pthread_mutex_unlock(philo->general->dead);
		print_msg("died", philo);
		return (1);
	}
	return (0);
}

int	coroutine_take_forks1(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	print_msg("has taken a fork 1", philo);
	pthread_mutex_lock(philo->fork_left);
	print_msg("has taken a fork 2", philo);
	if (coroutine_to_die(philo))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	return (0);
}

int	coroutine_take_forks2(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_msg("has taken a fork 1", philo);
	pthread_mutex_lock(philo->fork_right);
	print_msg("has taken a fork 2", philo);
	if (coroutine_to_die(philo))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	return (0);
}

int	coroutine_to_eat (t_philo *philo)
{
	print_msg("is eating", philo);
	if (wait_activity(philo->general->time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	philo->last_eat = get_timestamp();
	return (0);
}

int	coroutine_to_sleep (t_philo *philo)
{
	print_msg("is sleeping", philo);
	if (wait_activity(philo->general->time_to_sleep, philo))
		return (1);
	if (coroutine_to_die(philo))
		return (1);
	print_msg("is thinking", philo);
	usleep(50);
	return (0);
}