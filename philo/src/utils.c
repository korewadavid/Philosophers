/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:21:15 by damendez          #+#    #+#             */
/*   Updated: 2024/01/12 15:55:53 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_full(t_philo *philo)
{
	if (philo->data->total_meals
		>= (philo->data->philo_nb * philo->data->must_eat_nb))
	{
		pthread_mutex_unlock(&philo->data->m_last_meal_time);
		return (1);
	}
	return (0);
}

/* Returns 1 if a philo is dead
 * 1. check if a philo is full
 * 2. if time_to_die has passed since philos last meal its marked as dead 
*/
int	check_dead(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->m_last_meal_time);
	if (philo->data->must_eat_nb > 0)
		if (check_full(philo) == 1)
			return (1);
	pthread_mutex_unlock(&philo->data->m_last_meal_time);
	pthread_mutex_lock(&philo->data->m_check_dead);
	pthread_mutex_lock(&philo->data->m_print);
	time = time_now(philo);
	if (philo->data->dead == 1
		|| (time - philo->last_meal_time) >= philo->data->time_to_die
		|| philo->data->is_print)
	{
		philo->data->dead_time = time_now(philo);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->m_check_dead);
		pthread_mutex_unlock(&philo->data->m_print);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_check_dead);
	pthread_mutex_unlock(&philo->data->m_print);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	ft_free(void *f1, void *f2)
{
	free(f1);
	free(f2);
	return (1);
}

/*
 * 1) Skip leading whitespaces in the input string.
 * 2) Check for number sign and update variable
 * 3) Handle the case where the input string is empty after removing whitespaces.
 * 4) Iterate through the string while the characters are digits.
 * updating ret adding current char as an int
*/
long int	ft_atol(char *str)
{
	long int	res;
	long int	sign;
	long int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	while (ft_isdigit((int)str[i]) == 0)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}
