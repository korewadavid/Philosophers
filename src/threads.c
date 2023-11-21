/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:08:34 by damendez          #+#    #+#             */
/*   Updated: 2023/11/07 18:04:30 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/philo.h"



// Setup and manage threads
int		thread_init(t_data *data)
{
	// Make thread id buffer for monitor thread
	pthread_t	mt;
	int			i;
	
	// Get current time as reference point for the starting time of program
	
	// Create monitor thread
	if (pthread_create(&mt, NULL, &monitor, data->philos))
		

	// Create philosopher threads, return defined error on failure, in loop sleep between thread creation so their not all made at the same time
	
	// Wait for each philosopher thread to finish
	
	// Return 0 on success
}
