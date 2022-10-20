/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coroutine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:27:19 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/18 22:03:02 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

static int	coroutine_to_forks(t_philo *philo)
{
	
}

static int	coroutine_to_eat(t_philo *philo)
{
	
}

static int	coroutine_to_sleep_think(t_philo *philo)
{
	
}

void	*coroutine_philo(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->general->start);
	pthread_mutex_unlock(&philo->general->start);
	if (philo->num_philo % 2)
		usleep(philo->general->time_to_eat - 10);
	philo->last_eat == get_timestamp();
	while (check_death(philo) && (philo->general->nb_times_to_eat == -1
			|| check_all_philo_eat(philo->general, philo)))
	{
		if (coroutine_take_forks(philo))
			continue ;
		if (coroutine_to_eat(philo))
			continue ;
		if (coroutine_to_sleep_think(philo))
			continue ;		
		pthread_mutex_lock(&philo->general->eat);
		philo->general->nb_ate[philo->num_philo - 1] += 1;
		pthread_mutex_unlock(&philo->general->eat);
	}
	return ;
}
