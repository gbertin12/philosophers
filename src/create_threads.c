/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:47:28 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/08 12:38:21 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_t	*create_threads(t_philo *philo, int nb_philo)
{
	t_philo			*begin;
	pthread_t		thid[nb_philo];
	int				i;
	
	i = 0;
	begin = philo;
	while (begin != NULL)
	{
		if (pthread_create(&(thid[i]), NULL, &coroutine_philo, begin))
		{
			perror("");
			return (NULL);
		}
		begin = begin->next;
		i++;
	}
	begin = philo;
	i = 0;
	while(begin)
	{
		pthread_join(thid[i], NULL);
		i++;
		begin = begin->next;
	}
	return (NULL);
}
