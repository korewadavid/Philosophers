/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:28:22 by damendez          #+#    #+#             */
/*   Updated: 2024/01/22 16:52:43 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	one_philo_case(t_philo *philo)
{
	long	time;

	time = time_now(philo);
	// lock fork, print msg, sleep, then die
	pthread_mutex_lock(&philo->data->m_forks[philo->r_fork]);
	ft_print(philo, "has taken right fork");
	while (time_now(philo) < (time + philo->data->time_to_die))
		usleep(10);
	philo->data->dead_time = time_now(philo);
	pthread_mutex_unlock(&philo->data->m_forks[philo->r_fork]);
	philo->data->dead = 1;
}

static int	philo_sleep_think(t_philo *philo)
{
	long	time;

	if (ft_print(philo, "is sleeping") == 1)
		return (-1);
	time = time_now(philo);
	while (time_now(philo) < (time + philo->data->sleep_time))
	{
		if (check_dead(philo))
			return (-1);
		usleep(50);
	}
	if (ft_print(philo, "is thinking") == 1)
		return (-1);
	return (0);
}

static void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	printf("%lu\t%d\t%s\n", philo->data->dead_time, philo->philo_id, "died");
	pthread_mutex_unlock(&philo->data->m_print);
}

static void	final_check(t_philo *philo)
{
	long	time;

	time = time_now(philo);
	pthread_mutex_lock(&philo->data->m_check_dead);
	if (!philo->data->is_print && philo->data->dead == 1
		&& ((time - philo->last_meal_time) >= philo->data->time_to_die))
	{
		philo->data->is_print = 1;
		philo_die(philo);
	}
	pthread_mutex_unlock(&philo->data->m_check_dead);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->m_time);
	philo->data->start_time = get_time();
	pthread_mutex_unlock(&philo->data->m_time);
	while (1)
	{
		if (philo->data->philo_nb == 1)
		{
			one_philo_case(philo);
			break ;
		}
		if (philo_eat(philo) == -1)
			break;
		if (philo_sleep_think(philo) == -1) //prints and checks if a philo dies while sleeping
			break;
	}
	/*
	final_check:
		is_print: set when philo is ready to be classified in dead, used in check_dead
		philo_die: prints philo dead_time
	*/
	final_check(philo);
	return (NULL);
}
