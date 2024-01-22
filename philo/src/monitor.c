/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:08:23 by damendez          #+#    #+#             */
/*   Updated: 2024/01/22 16:53:39 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 * for each philo, if time has passed since their 
 * last meal time and that time is >= die_t,
 * and program hasnt been marked as finished, 
 * mark it as finished and print that the current philo died
*/
bool	philo_died(t_data *data)
{
	int				i;
	unsigned long	elapsed;
	unsigned long	t2;
	unsigned long	t1;

	i = -1;
	while (++i < data->philo_nb)
	{
		t2 = get_time();
		safe_mutex_handle(&data->philo[i].m_eating, LOCK);
		t1 = data->philo[i].last_meal_t;
		safe_mutex_handle(&data->philo[i].m_eating, UNLOCK);
		elapsed = t2 - t1;
		if (t2 > t1 && (elapsed >= data->die_t) && (data->finish == false))
		{
			safe_mutex_handle(&data->m_finish, LOCK);
			data->finish = true;
			safe_mutex_handle(&data->m_finish, UNLOCK);
			safe_mutex_handle(&data->philo[i].m_eating, LOCK);
			if (data->philo[i].eating == 0)
				ft_print_died(&data->philo[i], "died");
			safe_mutex_handle(&data->philo[i].m_eating, UNLOCK);
			return (true);
		}
	}
	return (false);
}

/*
 * If all of the philosophers have eaten at least 
 * meals_nb then mark 'finish' as true to finish simulation
*/
bool	all_finished(t_data *data)
{
	int	i;

	i = 0;
	if (data->meals > 0)
	{
		while (i < data->philo_nb)
		{
			safe_mutex_handle(&data->philo[i].m_eating, LOCK);
			if (i < data->philo_nb && data->philo[i].meals_done >= data->meals)
				i++;
			safe_mutex_handle(&data->philo[i].m_eating, UNLOCK);
		}
		if (i == data->philo_nb)
		{
			safe_mutex_handle(&data->m_finish, LOCK);
			data->finish = true;
			safe_mutex_handle(&data->m_finish, UNLOCK);
			return (true);
		}
	}
	return (false);
}

/*
 * Constently checks if a philo qualifies as dead or if theyve all eaten meal_nb
*/
void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->philo_nb == 1)
		return (NULL);
	while (1)
	{
		if (philo_died(data) == true)
			return (NULL);
		if (all_finished(data) == true)
			return (NULL);
	}
}
