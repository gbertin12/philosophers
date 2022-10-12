/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coroutine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:56:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/12 22:03:00 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_all_philo_eat(t_general *general)
{
	int i;

	i = 0;
	if (general->nb_times_to_eat == -1)
		return (1);
	while (i < general->nb_philo)
	{
		if (general->nb_ate[i] < general->nb_times_to_eat)
			return (1);
		i++;
	}
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
	t_philo 		*philo;
	int 			i;
	
	philo = (t_philo *)data;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(philo->general->eat);
		if (philo->general->start == philo->general->nb_philo)
		{
			pthread_mutex_unlock(philo->general->eat);
			break ;
		}
		pthread_mutex_unlock(philo->general->eat);
	}
	if (philo->num_philo == 1)
		philo->general->time_start = get_timestamp();
	else
		usleep(20);
	philo->last_eat = get_timestamp();
	while (!check_death(philo) 
	&& (philo->general->nb_times_to_eat == -1 || check_all_philo_eat(philo->general)))
	{
		coroutine(philo);
		pthread_mutex_lock(philo->general->eat);
		philo->general->nb_ate[philo->num_philo - 1] += 1;
		pthread_mutex_unlock(philo->general->eat);
		i++;
	}
	return (NULL);
}
