/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:08:34 by damendez          #+#    #+#             */
/*   Updated: 2023/11/01 16:19:42 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/philo.h"

// Setup and manage threads
int		thread_init(t_data *data)
{
	// Get current time as reference point for the starting time of program
	// If user gave a meals_nb create a "monitor" thread, return error on failure
	// Create philosopher threads, return defined error on failure, in loop sleep between thread creation so their not all made at the same time
	// Wait for each philosopher thread to finish
	// Return 0 on success
}
