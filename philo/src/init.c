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
		safe_mutex_handle(data->philos[i].m_eating, INIT);
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
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_nb);
	data->m_forks = safe_malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	while (++i < data->philo_nb)
		safe_mutex_handle(data->m_forks[i], INIT);
	safe_mutex_handle(data->m_finish, INIT);
	safe_mutex_handle(data->m_print, INIT);
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
