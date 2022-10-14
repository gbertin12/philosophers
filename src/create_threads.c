/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:47:28 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/14 11:36:12 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	launch_creating(t_philo *begin)
{
	t_philo			*philo;

	philo = begin;
	while (philo != NULL)
	{
		if (pthread_create(&(philo->thread_id), NULL, &coroutine_philo, philo))
		{
			perror("");
			return (1);
		}
		philo = philo->next;
	}
	return (0);
}

static void	join_threads(t_philo *begin)
{
	t_philo			*philo;

	philo = begin;
	while (philo)
	{
		pthread_join(philo->thread_id, NULL);
		philo = philo->next;
	}
}

int	create_threads(t_philo *begin)
{
	pthread_mutex_lock(&begin->general->start);
	if (launch_creating(begin))
		return (1);
	begin->general->time_start = get_timestamp();
	pthread_mutex_unlock(&begin->general->start);
	join_threads(begin);
	return (0);
}
