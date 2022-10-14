/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:30:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/14 10:23:31 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_general_mutex(t_general *general)
{
	if (general)
	{
		pthread_mutex_destroy(&general->dead);
		pthread_mutex_destroy(&general->write);
		pthread_mutex_destroy(&general->start);
		pthread_mutex_destroy(&general->eat);
	}
}

void	free_threads(t_philo *begin)
{
	t_philo	*philo;
	t_philo	*tmp;

	philo = begin;
	if (!philo)
		return ;
	while (philo->next)
	{
		tmp = philo;
		if (tmp->fork_left)
		{
			pthread_mutex_destroy(tmp->fork_left);
			free(philo->fork_left);
		}
		philo = tmp->next;
		free(tmp);
	}
	free(philo);
}

void	free_all(t_philo *philo)
{
	if (!philo)
		return ;
	if (philo->fork_left)
	{
		pthread_mutex_destroy(philo->fork_left);
		free(philo->fork_left);
	}
	if (philo->fork_right)
	{
		pthread_mutex_destroy(philo->fork_right);
		free(philo->fork_right);
	}
	free_threads(philo->next);
	free(philo->general->nb_ate);
	free(philo->general);
	free(philo);
}
