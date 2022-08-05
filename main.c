/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:32:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/04 19:47:10 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
I - Créer les philos dans des threads
II - Leur attribuer la fourchette gauche et la fourchette droite
III - Protéger les fourchettes avec des mutex



*/
int	main(int argc, char **argv)
{
	t_philo *philo;

	if (argc < 5 || argc > 6)
		return (1);
	// parsing
	philo = create_list_of_philo(argv);
		// Créer les philos dans des threads
	return (0);
}