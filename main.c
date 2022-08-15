/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:32:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/12 17:55:25 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
I - Créer les philos dans des threads
II - Leur attribuer la fourchette gauche et la fourchette droite
III - Protéger les fourchettes avec des mutex
*/

void print_philo(t_philo *philo)
{
	printf("fee\n");
	while(philo)
	{
		printf("%d %d %d %d %d\n", philo->num_philo, philo->time_to_die, philo->time_to_eat, philo->time_to_sleep, philo->nb_times_to_eat);
		philo = philo->next;
	}
}

int	main(int argc, char **argv)
{
	t_philo *philo;
	(void)argc;
	// if (argc < 5 || argc > 6)
	// 	return (1);
	// parsing
	philo = create_list_of_philo(argv);
	print_philo(philo);
		// Créer les philos dans des threads
	return (0);
}