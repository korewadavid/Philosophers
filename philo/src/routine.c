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
	pthread_mutex_lock(&philo->r_fork);
	ft_print(philo, "has taken right fork");
	while (time_now(philo) < (time + philo->data->time_to_die))
		usleep(10);
	philo->data->dead_time = time_now(philo);
	pthread_mutex_unlock(&philo->r_fork);
	philo->data->dead = 1;
}

static void	ft_sleep_think(t_philo *philo)
{
	safe_mutex_handle(&philo->data->m_finish, LOCK);
	if (philo->data->finish == true)
	{
		safe_mutex_handle(&philo->data->m_finish, UNLOCK);
		return ;
	}
	safe_mutex_handle(&philo->data->m_finish, UNLOCK);
	ft_print(philo, "is sleeping");
	ft_usleep(philo->data->sleep_t);
	ft_print(philo, "is thinking");
}

static void	ft_eat(t_philo *philo)
{
	safe_mutex_handle(&philo->data->m_finish, LOCK);
	if (philo->data->finish == true)
	{
		safe_mutex_handle(&philo->data->m_finish, UNLOCK);
		return ;
	}
	safe_mutex_handle(&philo->data->m_finish, UNLOCK);
	safe_mutex_handle(&philo->data->m_forks[philo->l_fork], LOCK);
	ft_print(philo, "has taken a fork");
	safe_mutex_handle(&philo->data->m_forks[philo->r_fork], LOCK);
	ft_print(philo, "has taken a fork");
	safe_mutex_handle(&philo->m_eating, LOCK);
	philo->eating = 1;
	philo->last_meal_t = get_time();
	ft_print(philo, "is eating");
	ft_usleep(philo->data->eat_t);
	safe_mutex_handle(&philo->m_meals, LOCK);
	philo->meals_done++; // DATA RACES
	safe_mutex_handle(&philo->m_meals, UNLOCK);
	philo->eating = 0;
	safe_mutex_handle(&philo->m_eating, UNLOCK);
	safe_mutex_handle(&philo->data->m_forks[philo->l_fork], UNLOCK);
	safe_mutex_handle(&philo->data->m_forks[philo->r_fork], UNLOCK);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	//TO-DOspinlock 

	while (1)
	{
		if (philo->data->philo_nb == 1)
		{
			one_philo_case(philo);
			break;
		}
		if (philo_eat(philo) == -1) // TO-DO
			break;
		if (philo_sleep(philo) == -1) // TO-DO
			break;
		if (philo_think(philo) == -1) // TO-DO
			break;
	}

	/*
	final_check:
		is_print: set when philo is ready to be classified in dead, used in check_dead
		philo_die: prints philo dead_time
	*/ 

	return (NULL);
}
