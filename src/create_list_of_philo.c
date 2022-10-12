/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_of_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:42:44 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/12 18:28:56 by gbertin          ###   ########.fr       */
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
