#include "../src/philo.h"

void	*monitor(void *data_pointer) // Why is the monitor function and parameter of 'void *' type?
{

}

void	*routine(void *philo_pointer)
{

}

int		thread_init(t_data *data)
{
	int i;
	pthread_t mt;
	// Get current time
	data->start_time = get_time();

	// If user entered optional number of meals, make monitor thread that will check to see if all the philosophers have eaten, checking for error incase thread creation failed
	if (data->meals_nb > 0)
	{
		if (pthread_create(&mt, NULL, &monitor, &data->philos[0])); // Why is the value of the 'arg' parameter that we send to the monitor function '&data->philos[0]'?
			return (error(TH_ERR, data)); // Why do we destroy all the mutexs incase of this error ?
	}

	// Now we will make a thread for each philosopher (Why are the philosophers threads? What is a thread?)
	i = 0;
	while (data->philo_num > i)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error(TH_ERR, data));
		i++;
	}

	// Now we wait for the philosopher threads to finish
	i = 0;
	while (data->philo_num > i)
	{
		if (pthread_join(&data->tid[i], NULL)) // How does pthread_join work? Why do we set the second parameter to NULL?
			return (error(JOIN_ERR, data));
	}
	return (0);
}

// Setup and manage threads
//int		thread_init(t_data *data)
//{
	// Make thread id buffer for

	// Get current time as reference point for the starting time of program

	// If user gave a meals_nb create a "monitor" thread, return error on failure

	// Create philosopher threads, return defined error on failure, in loop sleep between thread creation so their not all made at the same time
	
	// Wait for each philosopher thread to finish
	
	// Return 0 on success
//}
