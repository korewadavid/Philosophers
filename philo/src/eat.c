/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:24:38 by damendez          #+#    #+#             */
/*   Updated: 2024/01/31 18:17:10 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->m_forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->m_forks[philo->l_fork]);
	if (check_dead(philo))
		return (1);
	return (0);
}

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_forks[philo->r_fork]);
	if (ft_print(philo, "has taken right fork"))
	{
		pthread_mutex_unlock(&philo->data->m_forks[philo->r_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->m_forks[philo->l_fork]);
	if (ft_print(philo, "has taken left fork"))
	{
		drop_forks(philo);
		return (1);
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	long	time;

	if (specific_usleep(philo))
		return (-1);
	if (take_forks(philo))
		return (-1);
	if (ft_print(philo, "is eating"))
		return (-1);
	pthread_mutex_lock(&philo->data->m_last_meal_time);
	philo->data->total_meals++;
	pthread_mutex_unlock(&philo->data->m_last_meal_time);
	philo->ph_meal++;
	philo->last_meal_time = time_now(philo);
	time = time_now(philo);
	while (time_now(philo) < (time + philo->data->eat_time))
	{
		if (check_dead(philo))
		{
			drop_forks(philo);
			return (-1);
		}
		usleep(50);
	}
	return (drop_forks(philo));
}
