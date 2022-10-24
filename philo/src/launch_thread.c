/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:18:20 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/24 15:09:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	join_thread(pthread_t *tid, t_general *general)
{
	int	i;

	i = 0;
	while (i < general->nb_philo)
	{
		pthread_join(tid[i], NULL);
		i++;
	}
}

static long long	get_time_start(void)
{
	long long	time;

	time = get_timestamp();
	while (1)
	{
		if (time % 1000 == 0)
			return (time);
		time = get_timestamp();
	}
	return (0);
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
		if (pthread_create(&tid[i], NULL, coroutine_philo,
				(void *)(&general->philos[i])) != 0)
		{
			free(tid);
			return (1);
		}
		i++;
	}
	usleep(20000);
	general->time_start = get_time_start();
	pthread_mutex_unlock(&general->start);
	join_thread(tid, general);
	free(tid);
	return (1);
}
