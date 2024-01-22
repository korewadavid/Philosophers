/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:04:39 by damendez          #+#    #+#             */
/*   Updated: 2024/01/22 16:51:12 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	init_mutex(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->philo_nb)
	{
		safe_mutex_handle(&data->m_forks[i], INIT);
		safe_mutex_handle(&data->philo[i].m_eating, INIT);
		safe_mutex_handle(&data->philo[i].m_meals, INIT);
	}
	safe_mutex_handle(&data->m_print, INIT);
	safe_mutex_handle(&data->m_finish, INIT);
	return (0);
}

static int	init_philos(t_data *data)
{
	int		i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philo)
		return (1);
	while (++i < data->philo_nb)
	{
		data->philo[i].id = i + 1;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = i - 1;
		if (i == 0)
			data->philo[i].r_fork = data->philo_nb - 1;
		data->philo[i].data = data;
		data->philo[i].meals_done = 0;
		data->philo[i].last_meal_t = get_time();
		data->philo[i].eating = 0;
	}
	return (0);
}

static int	init_data(t_data *data, char **argv)
{
	int	i;

	i = -1;
	data->philo_nb = ft_atol(argv[1]);
	data->die_t = ft_atol(argv[2]);
	data->eat_t = ft_atol(argv[3]);
	data->sleep_t = ft_atol(argv[4]);
	data->meals = -1;
	if (argv[5])
		data->meals = ft_atol(argv[5]);
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->m_forks)
		return (1);
	while (++i < data->philo_nb)
		safe_mutex_handle(&data->m_forks[i], INIT);
	safe_mutex_handle(&data->m_print, INIT);
	data->finish = false;
	safe_mutex_handle(&data->m_finish, INIT);
	return (0);
}

/*
 * 1) Initiate data struct, save input variable values
 * 1.1) Safe allocate memory for philo and fork arrays
 * 2) Initalize each philo structs values and assign forks
 * 3) Initalize project mutexs (data mutexes for printing and 
 * for when program needs to finish, forks, and philo mutex for when eating)
*/
int	init_all(t_data *data, char **argv)
{
	if (init_data(data, argv))
		return (1);
	if (init_philos(data))
		return (1);
	if (init_mutex(data))
		return (1);
	return (0);
}
