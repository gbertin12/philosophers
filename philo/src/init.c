/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:25:42 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/24 16:28:30 by gbertin          ###   ########.fr       */
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

static int	init_rules(char **argv, t_general *general)
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
	if (general->time_to_die < 1 || general->time_to_eat < 1 || !general->nb_ate
		|| general->time_to_sleep < 1 || general->nb_philo < 1)
	{
		write(1, "Error Parsing\n", 15);
		return (1);
	}
	return (0);
}

static int	init_fork(t_general *general)
{
	int	i;

	i = 0;
	general->forks = malloc(sizeof(t_fork) * general->nb_philo);
	if (!general->forks)
		return (1);
	while (i < general->nb_philo)
	{
		ft_memset(&general->forks[i], 0, sizeof(t_fork));
		pthread_mutex_init(&general->forks[i].fork, NULL);
		i++;
	}
	return (0);
}

static int	init_philo(t_general *general)
{
	int	i;

	i = 0;
	general->philos = malloc(sizeof(t_philo) * general->nb_philo);
	if (!general->philos)
		return (1);
	while (i < general->nb_philo)
	{
		ft_memset(&general->philos[i], 0, sizeof(t_philo));
		general->philos[i].fork_left = i;
		general->philos[i].fork_right = (i + 1) % general->nb_philo;
		general->philos[i].last_eat = 0;
		general->philos[i].num_philo = i;
		general->philos[i].general = general;
		i++;
	}
	return (0);
}

t_general	*init_general(char **argv, t_general *general)
{
	general = malloc(sizeof(*general));
	if (!general)
		return (NULL);
	ft_memset(general, 0, sizeof(t_general));
	if (pthread_mutex_init(&general->start, NULL))
		return (msg_err("Init Error Start", general));
	if (pthread_mutex_init(&general->write, NULL))
		return (msg_err("Init Error Write", general));
	if (pthread_mutex_init(&general->dead, NULL))
		return (msg_err("Init Error Dead", general));
	if (pthread_mutex_init(&general->eat, NULL))
		return (msg_err("Init Error Eat", general));
	if (init_rules(argv, general))
		return (msg_err("", general));
	if (init_fork(general))
		return (msg_err("Error Fork\n", general));
	if (init_philo(general))
		return (msg_err("Error Philo\n", general));
	return (general);
}
