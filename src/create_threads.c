/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:47:28 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/13 12:05:01 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	lauch_creating(t_philo *begin)
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
	if (lauch_creating(begin))
		return (1);
	pthread_mutex_unlock(&begin->general->start);
	begin->general->time_start = get_timestamp();
	join_threads(begin);
	return (0);
}
