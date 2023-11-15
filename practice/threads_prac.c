#include "../src/philo.h"

void	*monitor(void *data_pointer) // Why is the monitor function and parameter of 'void *' type?
{

}

// supervises a single routine thread 
void	*supervisor(void *philo_pointer)
{

}

// routine for each philo
void	*routine(void *philo_pointer)
{
	// Cast the philo_pointer to a t_philo struct named philo (why?)
	
	// Calculate when current philo is supposed to die (time_to_die) and save in current philo struct, this will be used to keep in mind when a philo should die
	
	// Create new thread that supervises current philos time_to_die and eat_count, checking for error
	
	// While non of the philos have died make the current philo assigned by thread eat, sleep and think
	
	// Once 
}

// Setup and manage threads
int		thread_init(t_data *data)
{
	// Make thread id buffer for monitor thread
	pthread_t mt;

	// Get current time as reference point for the starting time of program
	data->start_time = get_time();

	// If user gave a meals_nb create a "monitor" thread, return error on failure
	if (data->meals_nb > 0)
		if (pthread_create(&mt, NULL, &monitor, ))
	
	// Wait for each philosopher thread to finish
	
	// Return 0 on success
}
