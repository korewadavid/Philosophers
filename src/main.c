/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/11/06 15:40:45 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_data(t_data *data)
{
	// if allocated memory pointers in data struct are present, free() them
}

void	ft_exit(t_data *data)
{
	// for each philosopher, eliminate forks and philo lock mutexs

	// eliminate the remaining mutexes in data struct

	// call clear_data
}

int	error(char *err, t_data *data)
{
	// Print error message

	// If data pointer was passed as paramter eliminate data stored

	// Return error value 1
}

int	check_input(int argc, char **argv)
{
	// Declare counter ints

	// Iterate through all of argv
			// if there are spaces present skip to the next iteration of the loop
			// if the current char is not valid (not a number), return error
}

int main(int argc, char **argv)
{
	// Declare pointer to program data struct

	// Check if number of input arguments is correct

	// Check if user input is correct (philo_num, death_time, eat_time, sleept_time) and check optional fifth argument meals_num

	// Initiate program structures (here we also check if input values are correct)

	// Run specific code in the case of one philosopher

	// Initiate threads for philosophers

	// Exit program by clearing all data once finished
}
