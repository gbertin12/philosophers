/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:51:00 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/23 07:43:30 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_fork	*create_fork()
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->lock = 0;
	if (pthread_mutex_init(&fork->fork, NULL) != 0)
		return (NULL);
	return (fork);
}

int		unlock_fork_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->general->forks[philo->fork_right].is_lock);	
	philo->general->forks[philo->fork_right].lock = 0;
	pthread_mutex_unlock(&philo->general->forks[philo->fork_right].is_lock);	
	pthread_mutex_unlock(&philo->general->forks[philo->fork_right].fork);
	return (0);
}

int		lock_fork_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->general->forks[philo->fork_right].is_lock);	
	if (philo->general->forks[philo->fork_right].lock)
	{
		pthread_mutex_unlock(&philo->general->forks[philo->fork_right].is_lock);	
		return (1);
	}
	philo->general->forks[philo->fork_right].lock = 1;
	pthread_mutex_unlock(&philo->general->forks[philo->fork_right].is_lock);	
	pthread_mutex_lock(&philo->general->forks[philo->fork_right].fork);
	return (0);
}

int		lock_fork_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->general->forks[philo->fork_left].is_lock);
	if (philo->general->forks[philo->fork_left].lock)
	{
		pthread_mutex_unlock(&philo->general->forks[philo->fork_left].is_lock);	
		unlock_fork_right(philo);
		return (1);
	}
	philo->general->forks[philo->fork_left].lock = 1;
	pthread_mutex_unlock(&philo->general->forks[philo->fork_left].is_lock);	
	pthread_mutex_lock(&philo->general->forks[philo->fork_left].fork);
	return (0);
}

int		unlock_fork_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->general->forks[philo->fork_left].is_lock);
	philo->general->forks[philo->fork_left].lock = 0;
	pthread_mutex_unlock(&philo->general->forks[philo->fork_left].is_lock);
	pthread_mutex_unlock(&philo->general->forks[philo->fork_left].fork);
	return (0);
}