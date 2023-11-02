#include "../src/philo.h"

void	init_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		//data->philos[i].thread = data->tid[i];
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].status = 0;
		data->philos[i].eating = 0;
		data->philos[i].time_to_die = data->death_time;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++
	}
}

int		init_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->philos[0].l_fork = data->forks[0];
	data->philos[0].r_fork = data->forks[i - 1];
	i = 1;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = data->forks[i];
		data->philos[i].r_fork = data->forks[i - 1];
		i++;
	}
	return (0);
}

int		alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->philo_num)
	if (!data->tid)
		return (error(ALLOC_ERR_1, NULL));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num)
	if (!data->forks)
		return (error(ALLOC_ERR_2, NULL));
	data->philos = malloc(sizeof(t_philo) * data->philo_num)
	if (!data->philos)
		return (error(ALLOC_ERR_3, NULL));
}

int		init_data(t_data *data, int argc, char **argv)
{
	data->philo_num = (int)ft_atoi(argv[1]);
	data->death_time = (u_int64_t)ft_atoi(argv[2]);
	data->eat_time = (u_int64_t)ft_atoi(argv[3]);
	data->sleep_time = (u_int64_t)ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_nb = (int)ft_atoi(argv[5]);
	else
		data->meals_nb = -1;
	if (data->philo_num <= 0 || data->philo_num >= 200 || data->death_time <= 0 || data->eat_time <= 0 || data->sleep_time <= 0 || (data->meals_nb <= 0 && data->meals_nb != -1 && argc == 6))
		return (error(ERR_IN_2, NULL));
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
}

void	init_program(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv))
		return (1);
	if (alloc(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_philos(data);
	return (0);
}

// void	init_philos(t_data *data)
// {
// 	// For each philo struct, initalize the struct values and lock mutex (? What does the lock mutex in the philo struct mean/represent?)
// }

// int		init_forks(t_data *data)
// {
// 	// For each philosopher in the program initalize a fork mutex with the correct corresponding fork mutex type as a parameter for each mutex
// 	// Assign the first philosophers left fork mutex value to the first fork mutex from data struct forks pointer, and the right one to the last fork
// 	// For the rest of the philosophers, assign their left and right fork values while the counter is less then the number of philosophers
// 	// Return 0 indicating correct completion of the function
// }

// int		alloc(t_data *data)
// {
// 	// Allocate memory for the correct ammount of thread IDs, fork mutex types and philosopher structs, checking for errors and returning addequete error message for each case
// }

// int		init_data(t_data *data, int argc, char **argv)
// {
//     // Equal t_data struct variables to the ones from the user input (philo_num, death_time, etc.), keep in mind meals_nb is optional
//     // Check if the values assigned to these variables are valid based on subject, if not print error INVALID INPUT VARIABLES
//     // Initalize current dead and finished values
//     // (? What does the write mutex and lock mutex from t_data struct mean/represent?)
// }

// void    init_program(t_data *data, int argc, char **argv);
// {
//     // Initalize data that comes from input arguments, checking if correct
//     // Initalize data that needs to be allocated with malloc
//     // Initalize mutex forks for program
//     // Initalize philospher data (? Why dont we check the init_philos function? Why did you choose not to make it return an int like init_data, init_philos and alloc?)
// 	// Return 0 representing correct completion of function
// }