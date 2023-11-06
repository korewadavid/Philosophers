/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:04:39 by damendez          #+#    #+#             */
/*   Updated: 2023/11/06 16:54:08 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Questions

	1. What does the lock mutex in t_data mean/do? 

void	init_philos(t_data *data)
{
	// For each philo struct, initalize the struct values and lock mutex (? What does the lock mutex in the philo struct mean/represent?)
}

int		init_forks(t_data *data)
{
	// For each philosopher in the program initalize a fork mutex with the correct corresponding fork mutex type as a parameter for each mutex
	
	// Assign the first philosophers left fork mutex value to the first fork mutex from data struct forks pointer, and the right one to the last fork
	
	// For the rest of the philosophers, assign their left and right fork values while the counter is less then the number of philosophers

	// Return 0 indicating correct completion of the function
}

int		alloc(t_data *data)
{
	// Allocate memory for the correct ammount of thread IDs, fork mutex types and philosopher structs, checking for errors and returning addequete error message for each case
}

int		init_data(t_data *data, int argc, char **argv)
{
	// Equal t_data struct variables to the ones from the user input (philo_num, death_time, etc.), keep in mind meals_nb is optional

	// Check if the values assigned to these variables are valid based on subject, if not print error INVALID INPUT VARIABLES

	// Initalize current dead and finished values
	
	// (? What does the write mutex and lock mutex from t_data struct mean/represent?)
}

void    init_program(t_data *data, int argc, char **argv)
{
	// Initalize data that comes from input arguments, checking if correct
	
	// Initalize data that needs to be allocated with malloc
	
	// Initalize mutex forks for program
	
	// Initalize philospher data (? Why dont we check the init_philos function? Why did you choose not to make it return an int like init_data, init_philos and alloc?)

	// Return 0 representing correct completion of function
}
