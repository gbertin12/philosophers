/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:14:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/18 16:35:37 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*msg_err(char *msg, t_philo *general)
{
	free_all(general);
	write(1, msg, ft_strlen(msg));
	return (NULL);
}

void	print_msg(char *msg, t_philo *philo)
{
	char *timestamp;

	pthread_mutex_lock(&philo->general->write);
	if (!check_death(philo))
	{
		pthread_mutex_lock(&philo->general->start);
		timestamp = ft_lltoa(get_timestamp() - philo->general->time_start);
		if (!timestamp)
			return ;
		write(1, timestamp, ft_strlen(timestamp));
		write(1, " ", 1);
		free(timestamp);
		timestamp = ft_lltoa((long long)philo->num_philo);
		if (!timestamp)
			return ;
		write(1, timestamp, ft_strlen(timestamp));
		free(timestamp);
		write(1, " ", 1);
		write(1, msg, ft_strlen(msg));
		write(1, "\n", 1);
		pthread_mutex_unlock(&philo->general->start);
	}
	pthread_mutex_unlock(&philo->general->write);
}
