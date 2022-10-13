/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:14:26 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/13 11:52:26 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*msg_err(char *msg, t_philo *begin)
{
	free_all(begin);
	write(1, msg, ft_strlen(msg));
	return (NULL);
}

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->general->write);
	if (!check_death(philo))
		printf("%lld %d %s\n",
			get_timestamp() - philo->general->time_start,
			philo->num_philo, msg);
	pthread_mutex_unlock(&philo->general->write);
}
