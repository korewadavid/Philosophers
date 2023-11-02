/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:08:34 by damendez          #+#    #+#             */
/*   Updated: 2023/11/02 16:57:40 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/philo.h"



// Setup and manage threads
int		thread_init(t_data *data)
{
	// Make thread id buffer for 
	pthread_t mt;
	
	// Get current time as reference point for the starting time of program
	data->start_time = get_time();	
	
	// If user gave a meals_nb create a "monitor" thread, return error on failure
	if (data->meals_nb > 0)
		pthread_create(&mt, NULL, )
	// Create philosopher threads, return defined error on failure, in loop sleep between thread creation so their not all made at the same time
	// Wait for each philosopher thread to finish
	// Return 0 on success
}
