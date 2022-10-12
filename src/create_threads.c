/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:47:28 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/12 22:07:27 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_t	*create_threads(t_philo *philo, int nb_philo)
{
	t_philo			*begin;
	int				i;
	
	(void)nb_philo;
	i = 0;
	begin = philo;
	while (begin != NULL)
	{
		if (pthread_create(&(begin->thread_id), NULL, &coroutine_philo, begin))
		{
			perror("");
			return (NULL);
		}
		pthread_mutex_lock(begin->general->eat);
		begin->general->start += 1;
		pthread_mutex_unlock(begin->general->eat);
		begin = begin->next;
		i++;
	}
	printf("after create all\n");
	begin = philo;
	i = 0;
	while(begin)
	{
		pthread_join(begin->thread_id, NULL);
		i++;
		begin = begin->next;
	}
	printf("after detach\n");
	return (NULL);
}
