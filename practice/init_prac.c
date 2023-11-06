#include "../src/philo.h"

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
}
