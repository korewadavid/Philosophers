/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:04:39 by damendez          #+#    #+#             */
/*   Updated: 2023/12/04 14:45:54 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Even | Odd fork assigment
*/

// static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
// {
// 	int philo_nbr;

// 	philo_nbr = philo->data->philo_nbr;

// 	if (philo->philo_id % 2 == 0)
// 	{
// 		philo->first_fork = &forks[philo_position];
// 		if (philo->philo_id == philo_nbr)
// 			philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
// 		else
// 			philo->second_fork = &forks[philo_position + 1];	
// 	}
// 	else
// 	{
// 		if (philo->philo_id == philo_nbr)
// 			philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
// 		else
// 			philo->first_fork = &forks[philo_position + 1];
// 		philo->second_fork = &forks[philo_position];
// 	}
// }

static int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		safe_mutex_handle(&data->forks[i], INIT);
		safe_mutex_handle(&data->philos[i].philo_mutex, INIT);
	}
	safe_mutex_handle(&data->data_mutex, INIT);
	safe_mutex_handle(&data->write_mutex, INIT);
	return (0);
}

static void	init_philos(t_data *data)
{
	int	i;
	
	i = -1;
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	while (++i < data->philo_nbr)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = i - 1;
		if (i == 0)
			data->philos[i].r_fork = data->philo_nb - 1;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		//data->philos[i].last_meal_time = 0;
		data->philos[i].eating = 0;
	}
	return (0);
}

static int	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->philo_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->nbr_max_meals = -1;
	if (argv[5])
		data->nbr_max_meals = ft_atol(argv[5]);
	data->end_simulation = false;
	//data->all_threads_ready = false;
	//data->threads_running_nbr = 0;
	data->forks = safe_malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	// safe_mutex_handle(&data->data_mutex, INIT);
	// safe_mutex_handle(&data->write_mutex, INIT);
	// while (++i < data->philo_nbr)
	// {
	// 	safe_mutex_handle(&data->forks[i].fork, INIT);
	// 	data->forks[i].fork_id = i;
	// }
	// philo_init(data);
	return (0);
}

int init_program(t_data *data, char **argv)
{
	if (init_data(data, argv))
		return (1);
	if (init_philos(data))
		return (1);
	if (init_mutex(data))
		return (1);
	return (0);
}
