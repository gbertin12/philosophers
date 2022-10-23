/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:18:20 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/23 07:17:31 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void join_thread(pthread_t	*tid, t_general *general)
{
	int	i;
	
	i = 0;
	while (i < general->nb_philo)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}

int	launch_thread(t_general *general)
{
	int			i;
	pthread_t	*tid;

	i = 0;
	tid = malloc(sizeof(pthread_t) * general->nb_philo);
	if (!tid)
		return (1);
	pthread_mutex_lock(&general->start);
	while (i < general->nb_philo)
	{
		if (pthread_create(&tid[i], NULL, coroutine_philo, (void *)(&general->philos[i])) != 0)
		{
			free(tid);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&general->start);
	general->time_start = get_timestamp();
	join_thread(tid, general);
	free(tid);
	return (1);
}