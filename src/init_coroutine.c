/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coroutine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:56:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/08 20:23:17 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	if (philo->num_philo == 1)
	{
		philo->general->time_start = get_timestamp();
		printf(" START = %lld\n", philo->general->time_start);
	}
	philo->last_eat = get_timestamp();
	while (!check_death(philo) 
	&& (philo->general->nb_times_to_eat == -1 || philo->general->nb_times_to_eat > i))
	{
		coroutine(philo);
		i++;
	}
	return (NULL);
}