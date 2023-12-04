/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:30:02 by damendez          #+#    #+#             */
/*   Updated: 2023/12/04 13:39:45 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Spinlock to synchronize philos start
void    wait_all_threads(t_data *data)
{
    while (!get_bool(&data->data_mutex, &data->all_threads_ready))
        ;
}

/*
 * Monitor waits untill
 * all the threads are running
*/
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, 
		long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

/*
 * Make the system fair for philos
*/
void	de_synchronize_philos(t_philo *philo)
{
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			precise_usleep(3e4, philo->data);
	}
	else
	{
		if (philo->philo_id % 2 == 0)
			thinking(philo, true);
	}	
}
