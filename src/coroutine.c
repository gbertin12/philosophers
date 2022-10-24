/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coroutine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:27:19 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/23 20:28:46 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_all_philo_eat(t_general *general, t_philo *philo)
{
	int	i;

	i = 0;
	if (general->nb_times_to_eat == -1)
		return (1);
	pthread_mutex_lock(&philo->general->eat);
	while (i < general->nb_philo)
	{
		if (general->nb_ate[i] < general->nb_times_to_eat)
		{
			pthread_mutex_unlock(&philo->general->eat);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->general->eat);
	return (0);
}

static int	coroutine_to_forks(t_philo *philo)
{
	if (get_timestamp() - philo->last_eat >= philo->general->time_to_die)
	{
		wait_to_die(philo);
		return (1);
	}
	if (lock_fork_right(philo))
		return (1);
	if (philo->general->forks[philo->fork_left].lock)
	{
		pthread_mutex_unlock(&philo->general->forks[philo->fork_right].fork);
		if (get_timestamp() - philo->last_eat >= philo->general->time_to_die)
			wait_to_die(philo);
		return (1);
	}
	if (lock_fork_left(philo))
	{
		unlock_fork_right(philo);
		return (1);
	}
	print_msg("has taken a fork\n", philo);
	print_msg("has taken a fork\n", philo);
	return (0);
}

static int	coroutine_to_eat(t_philo *philo)
{
	print_msg("is eating\n", philo);
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

static int	coroutine_to_sleep_think(t_philo *philo)
{
	print_msg("is sleeping\n", philo);
	if (wait_action(philo->general->time_to_sleep, philo))
		return (1);
	print_msg("is thinking\n", philo);
	usleep (100);
	return (0);
}

void	*coroutine_philo(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->general->start);
	pthread_mutex_unlock(&philo->general->start);
	if (philo->num_philo % 2)
		usleep(philo->general->time_to_eat - 10);
	philo->last_eat = get_timestamp();
	while (!check_death(philo) && (philo->general->nb_times_to_eat == -1
			|| check_all_philo_eat(philo->general, philo)))
	{
		if (coroutine_to_forks(philo))
			continue ;
		if (coroutine_to_eat(philo))
			continue ;
		if (coroutine_to_sleep_think(philo))
			continue ;
		if (philo->general->nb_times_to_eat != -1)
		{
			pthread_mutex_lock(&philo->general->eat);	
			philo->general->nb_ate[philo->num_philo - 1] += 1;
			pthread_mutex_unlock(&philo->general->eat);
		}
	}
	return (NULL);
}
