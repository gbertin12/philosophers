
#include "../includes/philo.h"

t_philo *create_list_of_philo(char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (NULL);
	ft_memset(philo, 0, sizeof(t_philo));
    if (!init_list(argv, philo))
        return (NULL);
	if (!add_all_philo_to_list(argv, philo))
		return (NULL);
	return (philo);
}


int		init_list(char **argv, t_philo *philo)
{
	pthread_mutex_t *fork_right = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t *fork_left = PTHREAD_MUTEX_INITIALIZER;

	philo->num_philo = 1;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		philo->nb_times_to_eat = -1;
	else
		philo->nb_times_to_eat = ft_atoi(argv[5]);
	philo->fork_right = fork_right;
	philo->fork_left = fork_left;
	philo->next = NULL;
	return (1);
}

int		add_all_philo_to_list(char **argv, t_philo *philo)
{
	int		nb_philo;
	int		i;
	t_philo	*first_philo;

	first_philo = philo;
	nb_philo = ft_atoi(argv[1]);
	i = 2;
	while (i < nb_philo)
	{
		if (!add_philo(argv, philo, i))
			return (0);
		philo = philo->next;
		i++;
	}
	if (!add_last_philo(argv, philo, first_philo, i))
		return (0);
	return (1);
}

int	add_philo(char **argv, t_philo *previous_philo, int num_philo)
{
	t_philo *new_philo;
	pthread_mutex_t *fork_left = PTHREAD_MUTEX_INITIALIZER;

	new_philo = malloc(sizeof(*new_philo));
	if (!new_philo)
		return (0);
	ft_memset(new_philo, 0, sizeof(t_philo));
	new_philo->num_philo = num_philo;
	new_philo->time_to_die = ft_atoi(argv[2]);
	new_philo->time_to_eat = ft_atoi(argv[3]);
	new_philo->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		new_philo->nb_times_to_eat = -1;
	else
		new_philo->nb_times_to_eat = ft_atoi(argv[5]);
	new_philo->fork_right = previous_philo->fork_left;
	new_philo->fork_left = fork_left;
	new_philo->next = NULL;
	previous_philo->next = new_philo;
	return (0);
}

int	add_last_philo(char **argv, t_philo *previous, t_philo *first, int num_philo)
{
	t_philo *new_philo;

	new_philo = malloc(sizeof(*new_philo));
	if (!new_philo)
		return (0);
	ft_memset(new_philo, 0, sizeof(t_philo));
	new_philo->num_philo = num_philo;
	new_philo->time_to_die = ft_atoi(argv[2]);
	new_philo->time_to_eat = ft_atoi(argv[3]);
	new_philo->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		new_philo->nb_times_to_eat = -1;
	else
		new_philo->nb_times_to_eat = ft_atoi(argv[5]);
	new_philo->fork_right = previous->fork_left;
	new_philo->fork_left = first->fork_right;
	new_philo->next = NULL;
	previous->next = new_philo;
}