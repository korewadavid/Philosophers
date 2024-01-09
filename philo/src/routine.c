/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:28:22 by damendez          #+#    #+#             */
/*   Updated: 2023/12/20 17:47:27 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_sleep_think(t_philo *philo)
{
	if (philo->data->finish == true)
		return ;
	ft_print(philo, "is sleeping");
	ft_usleep(philo->data->sleep_t);
	ft_print(philo, "is thinking");
}

static void	ft_eat(t_philo *philo)
{
	if (philo->data->finish == true)
		return ;
	pthread_mutex_lock(&philo->data->m_forks[philo->l_fork]);
	pthread_mutex_lock(&philo->data->m_forks[philo->r_fork]);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->m_eating);
	philo->eating = 1;
	philo->last_meal_t = get_time();
	ft_print(philo, "is eating");
	ft_usleep(philo->data->eat_t);
	philo->meals_done++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->m_eating);
	pthread_mutex_unlock(&philo->data->m_forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->m_forks[philo->r_fork]);
}

void	wait_start(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_t / 2);
	else if (philo->data->philo_nb % 2 != 0
		&& philo->id == philo->data->philo_nb)
		ft_usleep(philo->data->eat_t + 10);
}

/*
 * 1) First philo starts routine, every next one (2, 4, 6, etc.) will wait
 * 1.1) If theres and odd number of philosophers, last one must wait 2 wait cycles:
 * 2) Until the simulation must finish, philos will eat then sleep and think
 * 2.1) eat: grab forks -> print, update eating bool and last meal time -> print
 *      "eat" and update meals eaten then let go foks
 * 2.2) sleep: //
*/
void    *philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_nb == 1)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->l_fork]);
		ft_print(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->m_forks[philo->l_fork]);
		ft_usleep(philo->data->die_t);
		ft_print_died(philo->data->philo, "died");
		return (NULL);
	}
	wait_start(philo);
	while (1)
	{
		if (philo->data->finish == true)
			return (NULL);
		ft_eat(philo);
		ft_sleep_think(philo);
	}
	return (NULL);
}
