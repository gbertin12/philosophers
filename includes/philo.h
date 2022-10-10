/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:34:53 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/08 19:40:06 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct t_general
{
	int				death;
	long long		time_start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;
	pthread_mutex_t *write;
	pthread_mutex_t	*dead;
}			t_general;

typedef struct t_philo
{
	pthread_t		thread_id;
	long long		last_eat;
	int				num_philo;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
	t_general		*general;
	struct t_philo	*next;
}           t_philo;

// CREATE PHILO LIST
t_philo	*create_list_of_philo(char **argv);
int		init_list(char **argv, t_philo *philo);
int		add_all_philo_to_list(char **argv, t_philo *philo);
int		add_philo(t_philo *previous_philo, int num_philo);
int		add_last_philo(t_philo *previous, t_philo *first, int num_philo);
// MSG
t_philo *msg_err(char *msg);

//CHECK DEATH
int	check_death(t_philo *philo);

// GET TIMESTAMP
long long	get_timestamp();
int			wait_activity(int time, t_philo *philo);

//CREATE THREADS
pthread_t	*create_threads(t_philo *philo, int nb_philo);

// COROUTINE
void		*coroutine_philo(void *data);
int			coroutine_to_die(t_philo *philo);
int			coroutine_take_forks1(t_philo *philo);
int			coroutine_take_forks2(t_philo *philo);
int			coroutine_to_eat (t_philo *philo);
int			coroutine_to_sleep (t_philo *philo);
//FREE
void	free_all(t_philo *philo);

// UTILS 
void	*ft_memset(void *b, int c, size_t len);
int		ft_atoi(const char *str);
int		check_max_int(char *nbr);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
#endif
