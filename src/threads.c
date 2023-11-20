/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:08:34 by damendez          #+#    #+#             */
/*   Updated: 2023/11/20 16:58:13 by damendez         ###   ########.fr       */
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
	
	// Create a "monitor" thread, return error on failure
	if (pthread_create(&mt, NULL, &monitor, &data->philos))
		return (error(TH_ERR, data));

	// Create philosopher threads, return defined error on failure, in loop sleep between thread creation so their not all made at the same time
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error(TH_ERR, data));
		// why would we ft_usleep(1) here?
	}
	
	// Wait for each philosopher thread to finish
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error(JOIN_ERR, data));
	}	
	
	// Return 0 on success
	return (0);
}
