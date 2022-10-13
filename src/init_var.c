/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:28:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/13 11:41:33 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	*set_tab_int(int *tab, int size)
{
	int	i;

	i = 0;
	tab = malloc(sizeof(int) * size);
	if (!tab)
		return (NULL);
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}

static int	init_general_mutex(t_general *general)
{
	if (pthread_mutex_init(&general->write, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&general->dead, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&general->eat, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&general->start, NULL) != 0)
		return (1);
	return (0);
}

static void	init_rules(char **argv, t_general *general)
{
	general->death = 0;
	general->nb_philo = ft_atoi(argv[1]);
	general->nb_ate = set_tab_int(general->nb_ate, general->nb_philo);
	general->time_to_die = ft_atoi(argv[2]);
	general->time_to_eat = ft_atoi(argv[3]);
	general->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		general->nb_times_to_eat = -1;
	else
		general->nb_times_to_eat = ft_atoi(argv[5]);
}

static int	init_general(char **argv, t_philo *philo)
{
	t_general	*general;

	general = malloc(sizeof(*general));
	if (!general)
		return (1);
	ft_memset(general, 0, sizeof(t_general));
	if (init_general_mutex(general))
		return (1);
	init_rules(argv, general);
	if (general->time_to_die < 1 || general->time_to_eat < 1 || !general->nb_ate
		|| general->time_to_sleep < 1 || general->nb_philo < 1)
		return (1);
	philo->general = general;
	return (0);
}

int	init_list(char **argv, t_philo *philo)
{
	if (init_general(argv, philo))
		return (1);
	if (philo->general->nb_philo > 1)
	{
		philo->fork_left = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!philo->fork_left)
			return (1);
	}
	philo->fork_right = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->fork_right)
		return (1);
	philo->num_philo = 1;
	pthread_mutex_init(philo->fork_right, NULL);
	if (philo->general->nb_philo > 1)
		pthread_mutex_init(philo->fork_left, NULL);
	philo->next = NULL;
	return (0);
}
