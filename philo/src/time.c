/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:46 by damendez          #+#    #+#             */
/*   Updated: 2024/01/31 18:34:28 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	specific_usleep(t_philo *philo)
{
	unsigned long	time;
	unsigned long	end;

	time = 0;
	if (!philo->ph_meal && philo->philo_id % 2 != 0
		&& philo->data->philo_nb != philo->philo_id)
		return (0);
	else if (!philo->ph_meal && philo->philo_id % 2 == 0)
		time = philo->data->eat_time;
	else if (!philo->ph_meal && philo->data->philo_nb != 0
		&& philo->data->philo_nb == philo->philo_id)
		time = philo->data->eat_time * 2;
	else if (philo->ph_meal && philo->data->philo_nb % 2 != 0)
		time = (philo->data->eat_time * 2) - philo->data->sleep_time;
	else if (philo->ph_meal && philo->data->philo_nb % 2 == 0)
		time = philo->data->eat_time - philo->data->sleep_time;
	end = time_now(philo) + time;
	while (time_now(philo) < end)
	{
		if (check_dead(philo))
			return (1);
		usleep(50);
	}
	return (0);
}

unsigned long	time_now(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->m_time);
	time = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->m_time);
	return (time);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
