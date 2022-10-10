/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_of_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:42:44 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/08 12:31:26 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*create_list_of_philo(char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (msg_err("Error malloc philo\n"));
	ft_memset(philo, 0, sizeof(t_philo));
	if (!init_list(argv, philo))
		return (msg_err("Init List error\n"));
	if (!add_all_philo_to_list(argv, philo))
		return (msg_err("Add List error\n"));
	return (philo);
}

int	init_general(char **argv, t_philo *philo)
{
	t_general *general;

	general = malloc(sizeof(*general));
	if (!general)
		return (1);
	ft_memset(general, 0, sizeof(t_general));
	general->dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	general->write = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(general->write, NULL);
	pthread_mutex_init(general->dead, NULL);
	general->death = 0;
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
	philo->fork_left = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->fork_right = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->num_philo = 1;
	pthread_mutex_init(philo->fork_left, NULL);
	pthread_mutex_init(philo->fork_right, NULL);
	if (init_general(argv, philo))
		return (0);
	philo->next = NULL;
	return (1);
}

int	add_all_philo_to_list(char **argv, t_philo *philo)
{
	int		nb_philo;
	int		i;
	t_philo	*first_philo;

	first_philo = philo;
	nb_philo = ft_atoi(argv[1]);
	i = 2;
	while (i < nb_philo)
	{
		if (!add_philo( philo, i))
			return (0);
		philo = philo->next;
		i++;
	}
	if (!add_last_philo(philo, first_philo, i))
		return (0);
	return (1);
}

int	add_philo(t_philo *previous_philo, int num_philo)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(*new_philo));
	if (!new_philo)
		return (0);
	ft_memset(new_philo, 0, sizeof(t_philo));
	new_philo->fork_left = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	new_philo->num_philo = num_philo;
	new_philo->general = previous_philo->general;
	new_philo->fork_right = previous_philo->fork_left;
	pthread_mutex_init(new_philo->fork_left, NULL);
	new_philo->next = NULL;
	previous_philo->next = new_philo;
	return (1);
}

int	add_last_philo(t_philo *prev, t_philo *first, int num_philo)
{
	t_philo	*new_philo;
	
	new_philo = malloc(sizeof(*new_philo));
	if (!new_philo)
		return (0);
	ft_memset(new_philo, 0, sizeof(t_philo));
	new_philo->general = prev->general;
	new_philo->num_philo = num_philo;
	new_philo->fork_right = prev->fork_left;
	new_philo->fork_left = first->fork_right;
	new_philo->next = NULL;
	prev->next = new_philo;
	return (1);
}
