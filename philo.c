/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:32:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/07 15:41:41 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
I - Créer les philos dans des threads
II - Leur attribuer la fourchette gauche et la fourchette droite
III - Protéger les fourchettes avec des mutex
*/

int	check_entry(int	argc, char **argv)
{
	int	nb_arg;
	int	i;

	nb_arg = 1;
	while (nb_arg < argc)
	{
		i = 0;
		while (argv[nb_arg][i])
		{
			if (!ft_isdigit(argv[nb_arg][i]))
				return (1);
			i++;
		}
		if(!check_max_int(argv[nb_arg]))
			return (1);
		nb_arg++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo *philo;
	pthread_t *thid;
	(void)argc;
	
	if (argc < 5 || argc > 6)
		return (1);
	if (check_entry(argc, argv))
	{
		write(2, "Error Parsing\n", 15);
		return (1);
	}
		
	// parsing
	philo = create_list_of_philo(argv);
		// Créer les philos dans des threads
	thid = create_threads(philo, ft_atoi(argv[1]));
	//detach_all(philo);
	free_all(philo);
	return (0);
}