/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_coroutine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:56:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/14 12:37:21 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	check_all_philo_eat(t_general *general, t_philo *philo)
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

static void	coroutine(t_philo *philo)
{
	if (coroutine_to_die(philo))
		return ;
	if (philo->num_philo % 2)
	{
		if (coroutine_take_forks1(philo))
			return ;
	}
	else
	{
		if (coroutine_take_forks2(philo))
			return ;
	}
	if (coroutine_to_eat(philo))
		return ;
	if (coroutine_to_sleep(philo))
		return ;
	return ;
}

void	*coroutine_philo(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	pthread_mutex_lock(&philo->general->start);
	pthread_mutex_unlock(&philo->general->start);
	philo->last_eat = get_timestamp();
	if (philo->num_philo != 1 && philo->num_philo % 2)
		usleep(1000);
	else if (philo->num_philo != 1)
		usleep(500);
	while (!check_death(philo)
		&& (philo->general->nb_times_to_eat == -1
			|| check_all_philo_eat(philo->general, philo)))
	{
		coroutine(philo);
		pthread_mutex_lock(&philo->general->eat);
		philo->general->nb_ate[philo->num_philo - 1] += 1;
		pthread_mutex_unlock(&philo->general->eat);
		i++;
	}
	return (NULL);
}
