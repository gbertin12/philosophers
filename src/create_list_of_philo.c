/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_of_philo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:42:44 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/13 11:32:23 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*create_list_of_philo(char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (msg_err("Error malloc philo\n", philo));
	ft_memset(philo, 0, sizeof(t_philo));
	if (init_list(argv, philo))
		return (msg_err("Init List error\n", philo));
	if (!add_all_philo_to_list(philo))
		return (msg_err("Add List error\n", philo));
	return (philo);
}

int	add_all_philo_to_list(t_philo *philo)
{
	int		i;
	t_philo	*first_philo;

	first_philo = philo;
	i = 2;
	while (i < philo->general->nb_philo)
	{
		if (add_philo(philo, i))
			return (0);
		philo = philo->next;
		i++;
	}
	if (add_last_philo(philo, first_philo, i))
		return (0);
	return (1);
}

int	add_philo(t_philo *previous_philo, int num_philo)
{
	t_philo	*new_philo;

	if (previous_philo->general->nb_philo == 1)
		return (0);
	new_philo = malloc(sizeof(*new_philo));
	if (!new_philo)
		return (1);
	ft_memset(new_philo, 0, sizeof(t_philo));
	new_philo->fork_left = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!new_philo->fork_left)
		return (1);
	new_philo->num_philo = num_philo;
	new_philo->general = previous_philo->general;
	new_philo->fork_right = previous_philo->fork_left;
	pthread_mutex_init(new_philo->fork_left, NULL);
	new_philo->next = NULL;
	previous_philo->next = new_philo;
	return (0);
}

int	add_last_philo(t_philo *prev, t_philo *first, int num_philo)
{
	t_philo	*new_philo;

	if (first->general->nb_philo == 1)
		return (0);
	new_philo = malloc(sizeof(*new_philo));
	if (!new_philo)
		return (1);
	ft_memset(new_philo, 0, sizeof(t_philo));
	new_philo->general = prev->general;
	new_philo->num_philo = num_philo;
	new_philo->fork_right = prev->fork_left;
	new_philo->fork_left = first->fork_right;
	new_philo->next = NULL;
	prev->next = new_philo;
	return (0);
}
