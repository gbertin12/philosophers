/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:32:08 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/14 15:35:04 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	check_entry(int argc, char **argv)
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
		if (!check_max_int(argv[nb_arg]))
			return (1);
		nb_arg++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc < 5 || argc > 6 || check_entry(argc, argv))
	{
		write(2, "Parsing Error\n", 15);
		return (1);
	}
	philo = create_list_of_philo(argv);
	if (!philo)
		return (1);
	create_threads(philo);
	free_all(philo);
	return (0);
}
