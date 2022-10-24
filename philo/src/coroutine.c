/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coroutine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:27:19 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/24 16:15:36 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	coroutine_to_forks(t_philo *philo)
{
	if (get_timestamp() - philo->last_eat >= philo->general->time_to_die)
	{
		wait_to_die(philo);
		return (1);
	}
	if (lock_fork_right(philo))
	{
		usleep(100);
		return (1);
	}
	if (lock_fork_left(philo))
	{
		usleep(100);
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
	unlock_fork_right(philo);
	unlock_fork_left(philo);
	return (0);
}

static int	coroutine_to_sleep_think(t_philo *philo)
{
	print_msg("is sleeping\n", philo);
	if (wait_action(philo->general->time_to_sleep, philo))
		return (1);
	print_msg("is thinking\n", philo);
	return (0);
}

void	coroutine(t_philo *philo)
{
	if (coroutine_to_forks(philo))
		return ;
	if (coroutine_to_eat(philo))
		return ;
	if (coroutine_to_sleep_think(philo))
		return ;
	if (philo->general->nb_times_to_eat != -1)
	{
		pthread_mutex_lock(&philo->general->eat);
		philo->general->nb_ate[philo->num_philo] += 1;
		pthread_mutex_unlock(&philo->general->eat);
	}
}

void	*coroutine_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->general->start);
	philo->time_start = philo->general->time_start;
	pthread_mutex_unlock(&philo->general->start);
	if (philo->num_philo % 2)
		usleep(philo->general->time_to_eat);
	philo->last_eat = get_timestamp();
	while (!check_death(philo) && (philo->general->nb_times_to_eat == -1
			|| check_all_philo_eat(philo->general, philo)))
	{
		coroutine(philo);
	}
	return (NULL);
}
