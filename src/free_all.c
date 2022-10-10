/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:30:45 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/07 14:46:16 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_philo *philo)
{
	t_philo *begin;
	t_philo	*tmp;
	
	begin = philo;
	pthread_mutex_destroy(begin->fork_left);
	pthread_mutex_destroy(begin->fork_right);
	pthread_mutex_destroy(begin->general->dead);
	begin = begin->next;
	while (begin->next)
	{
		tmp = begin;
		pthread_mutex_destroy(tmp->fork_left);
		begin = tmp->next;
		free(tmp);
	}
	free(begin);
}
