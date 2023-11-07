#include "../src/philo.h"

/*
	Questions

	1. What does the lock mutex in t_data mean/do?
	2. in alloc(), in case of error we return (error(ALLOC_ERR_1, data)), justify why we pass data as a parameter here
*/

void	init_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		data->philos[i].time_to_die = data->death_time;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	init_forks(t_data *data)
{
	// for each philosopher, set up da fork
	int i;

	i = 0;
	while (i < data->philo_num)
		pthread_mutex_init(&data->forks[i++], NULL);
	
	// the first philosophers right fork is going to be the last array object, and left fork will be the first one
	data->philos[0].r_fork = data->forks[i - 1];
	data->philos[0].l_fork = data->forks[0];

	// assign rest of philosophers right and left forks
	i = 1;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = data->forks[i];
		data->philos[i].r_fork = data->forks[i - 1];
		i++;
	}
	return (0);
}

int	alloc(t_data *data)
{
	// allocate array of thread identifiers (per philosopher), checking for allocation error and returning error
	data->tid = malloc(sizeof(pthread_t) * data->philo_num)
	if (!data->tid)
		return (error(ALLOC_ERR_1, data));
	data->philos = malloc(sizeof(t_philo) * data->philo_num)
	if (!data->philos)
		return (error(ALLOC_ERR_2, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num)
	if (!data->forks)
		return (error(ALLOC_ERR_3, data));
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	// Equal data from struct to input arguments
	data->philo_num = (int)ft_atoi(argv[1]);
	data->death_time = (u_int64_t)ft_atoi(argv[2]);
	data->eat_time = (u_int64_t)ft_atoi(argv[3]);
	data->sleep_time = (u_int64_t)ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_nb = (int)ft_atoi(argv[5]);
	else
		data->meals_nb = -1;

	// Check if the values are valid based on subject (max philos 200)
	if (data->philo_num < 1 || data->philo_num >= 200 || data->death_time < 1 || data->eat_time < 1 || data->sleep_time < 1 || (data->meals_nb != 1 && data->meals_nb < 1))
		return (error(ERR_IN_2, NULL));
	
	// Set current dead and finished values
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	return (0);
}

int	init_program(t_data *data, int argc, char **argv)
{
	// Initiate data struct variables that are given by the user, checking if it returns correct
	if (init_data(data, argc, argv));
		return (1);
	
	// Initiate info from data struct that needs to be allocated
	if (alloc(data));
		return (1);

	// Initiate fork mutexes for program
	if (init_forks(data));
		return (1);
	
	// set up philosopher struct data
	init_philos(data);
	return (0);
}
