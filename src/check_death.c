/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:53:00 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/13 08:08:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->general->dead);
	if (philo->general->death == 1)
	{
		pthread_mutex_unlock(&philo->general->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->general->dead);
	return (0);
}
