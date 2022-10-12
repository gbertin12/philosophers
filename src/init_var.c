/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:28:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/12 21:57:18 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	*set_tab_in(int *tab, int size)
{
	int i;
	
	i = 0;
	tab = malloc(sizeof(int) * size);
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}

int	init_general(char **argv, t_philo *philo)
{
	t_general *general;

	general = malloc(sizeof(*general));
	if (!general)
		return (1);
	ft_memset(general, 0, sizeof(t_general));
	general->dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	general->eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	general->write = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!general->write || !general->eat || !general->dead)
		return (1);
	pthread_mutex_init(general->write, NULL);
	pthread_mutex_init(general->dead, NULL);
	pthread_mutex_init(general->eat, NULL);
	general->death = 0;
	general->nb_philo = ft_atoi(argv[1]);
	general->nb_ate = set_tab_in(general->nb_ate, general->nb_philo);
	general->start = 0;
	general->time_to_die = ft_atoi(argv[2]);
	general->time_to_eat = ft_atoi(argv[3]);
	general->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		general->nb_times_to_eat = -1;
	else
		general->nb_times_to_eat = ft_atoi(argv[5]);
	philo->general = general;
	return (0);
}

int	init_list(char **argv, t_philo *philo)
{
	if (init_general(argv, philo))
		return (0);
	philo->fork_right = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->num_philo = 1;
	pthread_mutex_init(philo->fork_right, NULL);

	if (philo->general->nb_philo > 1)
	{
		philo->fork_left = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo->fork_left, NULL);
	}
	philo->next = NULL;
	return (1);
}
