/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nb_ate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:03:22 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/24 12:03:41 by gbertin          ###   ########.fr       */
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
