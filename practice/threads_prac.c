#include "../src/philo.h"

void	*monitor(void *data_pointer) // Why is the monitor function and parameter of 'void *' type?
{

}

void	*routine(void *philo_pointer)
{

}

// Set up and manage threads
int		thread_init(t_data *data)
{
	int i;
	pthread_t mt;

	// get threads start time
	data->start_time = get_time();

	// if user entered num of meals for philosophers make a monitor thread to make sure they eaten num of meals
	if (data->meals_nb > 0)
	{
		
	}
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
