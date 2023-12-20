/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:04:39 by damendez          #+#    #+#             */
/*   Updated: 2023/12/20 17:26:51 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = i - 1;
		if (i == 0)
			data->philos[i].r_fork = data->philo_nb - 1;
		data->philos[i].meals_done = 0;
		data->philos[i].eating = false;
		// not last_meal_t, i want to set it when the simulation starts
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].m_eating, NULL) != 0)
			return (1);
	}
	return (0);
}

static int	init_data(t_data *data, char **argv)
{
	int i;

	i = -1;
	data->philo_nb = ft_atol(argv[1]);
	data->die_t = ft_atol(argv[2]);
	data->eat_t = ft_atol(argv[3]);
	data->sleep_t = ft_atol(argv[4]);
	data->meals_nb = -1;
	if (argv[5])
		data->meals_nb = ft_atol(argv[5]);
	data->finish = false;
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (1);
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->m_forks)
		return (1);
	while (++i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&data->m_finish, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
		return (1);
	return (0);
}

/*
 * 1) Initiate data struct, save input variable values
 * 1.1) Safe allocate memory for philo and fork arrays
 * 2) Initalize each philo structs values and assign forks
 * 3) Initalize project mutexs (data mutexes for printing and 
 * for when program needs to finish, forks, and philo mutex for when eating)
*/
int init_all(t_data *data, char **argv)
{
	if (init_data(data, argv))
		return (1);
	if (init_philos(data))
		return (1);
	return (0);
}
