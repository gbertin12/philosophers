/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:30:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/23 07:39:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_general_mutex(t_general *general)
{
	pthread_mutex_destroy(&general->dead);
	pthread_mutex_destroy(&general->write);
	pthread_mutex_destroy(&general->start);
	pthread_mutex_destroy(&general->eat);
}

void	free_forks(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->nb_philo)
	{
		pthread_mutex_destroy(&general->forks[i].fork);
		pthread_mutex_destroy(&general->forks[i].is_lock);
		i++;
	}
	free(general->forks);
}

void	free_all(t_general *general)
{
	if (!general)
		return ;
	free_general_mutex(general);
	free(general->nb_ate);
	free(general->philos);
	free(general);
}
