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

/*
 * for each philo, if time has passed since their last meal time and that time is >= die_t
 *, and program hasnt been marked as finished, mark it as finished and print that the current philo died
*/
static bool	philo_died(t_data *data)
{
	int	i;
	unsigned long	elapsed;
	unsigned long	t1;
	unsigned long	t2;

	i = -1;
	while (++i < data->philo_nb)
	{
		t2 = get_time();
		t1 = data->philo[i].last_meal_t;
		elapsed = t2 - t1;
		if (t1 < t2 && (elapsed >= data->die_t) && (data->finish != true))
		{
			safe_mutex_handle(&data->m_finish, LOCK);
			data->finish = true;
			safe_mutex_handle(&data->philo[i].m_eating, LOCK);
			if (data->philo[i].eating == 0)
			{
				safe_mutex_handle(&data->m_print, LOCK);
				ft_print_died(&data->philo[i], "died");
				safe_mutex_handle(&data->m_print, UNLOCK);
			}
			safe_mutex_handle(&data->philo[i].m_eating, UNLOCK);
			return (true);
		}
	}
	return (false);
}

static bool	philos_finished(t_philo *philo)
{

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
		if (philos_finished(data) == true)
			return (NULL);
	}
}
