/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:48:40 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/13 11:33:59 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_int(int i, char *nbr, char *max)
{
	while (nbr[i] == '0' && nbr[i + 1] != 0)
	{
		if (ft_strlen(&nbr[i]) < 10)
			return (1);
		i++;
	}
	if (ft_strlen(&nbr[i]) > 10)
		return (0);
	while (nbr[i] && *max)
	{
		if (*max < nbr[i])
			return (0);
		else if (*max > nbr[i])
			return (1);
		max++;
		i++;
	}
	return (1);
}

int	check_max_int(char *nbr)
{
	char	*max;
	int		i;

	i = 0;
	max = "2147483647";
	if (ft_strlen(nbr) < 10)
		return (1);
	if (ft_strlen(nbr) < 11 && nbr[0] == '-')
		return (1);
	if (nbr[0] == '-')
	{
		max = "2147483648";
		i++;
	}
	if (!check_int(i, nbr, max))
		return (0);
	return (1);
}
