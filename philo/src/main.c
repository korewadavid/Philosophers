/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2024/01/31 21:08:29 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	start_threads(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->philo_nb)
		if (pthread_create(&data->philos[i].thread_id, NULL, \
			philo_routine, &data->philos[i]))
			return (error_msg("pthread_create() error", 1));
	i = -1;
	while (++i < data->philo_nb)
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (error_msg("pthread_join() error", 1));
	return (0);
}

static int	free_all(t_data *data, int ret)
{
	int	i;

	free(data->philos);
	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->m_forks[i]);
	free(data->m_forks);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_check_dead);
	pthread_mutex_destroy(&data->m_time);
	pthread_mutex_destroy(&data->m_last_meal_time);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv)) // TO-DO
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	if (start_threads(&data))
		return (free_all(&data, 1));
	return (free_all(&data, 0));
}
