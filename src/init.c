/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:04:39 by damendez          #+#    #+#             */
/*   Updated: 2023/11/30 16:44:39 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Even | Odd fork assigment
*/

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int philo_nbr;

	philo_nbr = philo->table->philo_nbr;

	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = forks[philo_position];
		if (philo->philo_id == philo_nbr)
			philo->second_fork = forks[(philo_position + 1) % philo_nbr];
		else
			philo->second_fork = forks[philo_position + 1];	
	}
	else
	{
		if (philo->philo_id == philo_nbr)
			philo->first_fork = forks[(philo_position + 1) % philo_nbr];
		else
			philo->first_fork = forks[philo_position + 1];
		philo->second_fork = forks[philo_position];
	}
}

static void	philo_init(t_data *data)
{
	int	i;
	t_philo *philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philo + i;
		philo->philo_id = i + 1;
		philo->full = false;
		philo->eat_count = 0;
		philo->data = data;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, data->forks, i);
	}
}

void	init_data(t_data *data)
{
	int	i;

	i == -1;
	data->end_program = false;
	data->all_threads_ready = false;
	data->threads_running_nbr = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks = safe_malloc(sizeof(t_fork) * data->philo_nbr);
	safe_mutex_handle(data->data_mutex, INIT);
	while (++i < data->philo_nbr)
	{
		safe_mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	philo_init(data) //TO-DO
}
