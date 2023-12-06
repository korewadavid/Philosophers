/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:08:23 by damendez          #+#    #+#             */
/*   Updated: 2023/12/05 17:02:07 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
		
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->data->time_to_die / 1e3;

	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_routine(void *edata)
{
	int		i;
	t_data	*data;

	data = (t_data *)edata;

	while (!all_threads_running(&data->data_mutex, 
			&data->threads_running_nbr, data->philo_nbr))
		;
	while (!simulation_finished(data))
	{
		i = -1;
		while (++i < data->philo_nbr && !simulation_finished(data))
		{
			if (philo_died(data->philos + i))
			{
				set_bool(&data->data_mutex, &data->end_simulation, true);
				write_status(DIED, data->philos + 1, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
