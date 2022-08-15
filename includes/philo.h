/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:34:53 by gbertin           #+#    #+#             */
/*   Updated: 2022/08/12 18:37:26 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct t_philo
{
	pthread_t		thread_id;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;
	pthread_mutex_t	fork_right;
	pthread_mutex_t	fork_left;
	struct t_philo			*next;
}           t_philo;

// CREATE PHILO LIST
t_philo	*create_list_of_philo(char **argv);
int		init_list(char **argv, t_philo *philo);
int		add_all_philo_to_list(char **argv, t_philo *philo);
int		add_philo(char **argv, t_philo *previous_philo, int num_philo);
int		add_last_philo(char **argv, t_philo *previous, t_philo *first, int num_philo);
// MSG
t_philo *msg_err(char *msg);
// UTILS 
void	*ft_memset(void *b, int c, size_t len);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
#endif
