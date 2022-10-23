/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:34:53 by gbertin           #+#    #+#             */
/*   Updated: 2022/10/23 07:37:47 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct t_fork
{
	pthread_mutex_t	fork;
	pthread_mutex_t	is_lock;
	int				lock;
	
}				t_fork;

typedef struct t_general
{
	int				death;
	long long		time_start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_to_eat;
	int				*nb_ate;
	int				nb_philo;
	t_fork			*forks;
	struct t_philo	*philos;
	pthread_mutex_t	start;
	pthread_mutex_t	eat;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
}			t_general;

typedef struct t_philo
{
	long long		last_eat;
	int				num_philo;
	int				fork_left;
	int				fork_right;
	t_general		*general;
}				t_philo;


t_general *init_general(char **argv, t_general *general);

// MSG
t_general		*msg_err(char *msg, t_general *general);
void			print_msg(char *msg, t_philo *philo);

//HANDLE FORK
int			lock_fork_right(t_philo *philo);
int			lock_fork_left(t_philo *philo);
int			unlock_fork_right(t_philo *philo);
int			unlock_fork_left(t_philo *philo);

//TIMESTAMP
void		wait_to_die(t_philo *philo);
long long	get_timestamp(void);
int			wait_action(int time, t_philo *philo);

//CHECK DEATH
int			check_death(t_philo *philo);
int			coroutine_to_die(t_philo *philo);

// COROUTINE
void		*coroutine_philo(void *data);

//FREE
void		free_all(t_general *general);

// UTILS 
void		*ft_memset(void *b, int c, size_t len);
int			ft_atoi(const char *str);
int			check_max_int(char *nbr);
int			ft_strlen(char *str);
int			ft_isdigit(int c);
char		*ft_lltoa(long long n);

//INIT
t_general	*init_general(char **argv, t_general *general);

//CREATE THREADS
int			launch_thread(t_general *general);


#endif
