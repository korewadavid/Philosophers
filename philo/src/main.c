/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2024/01/22 14:28:10 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	start_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;
	pthread_t	*philo_th;

	i = -1;
	philo_th = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_nb);
	if (!philo_th)
		return (1);
	data->start_t = get_time();
	while (++i < data->philo_nb)
		safe_thread_handle(&philo_th[i], &philo_routine,
			&data->philo[i], CREATE);
	safe_thread_handle(&monitor, &monitor_routine, data, CREATE);
	i = -1;
	while (++i < data->philo_nb)
		safe_thread_handle(&philo_th[i], NULL, NULL, JOIN);
	safe_thread_handle(&monitor, NULL, NULL, JOIN);
	free(philo_th);
	return (0);
}

static void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		safe_mutex_handle(&data->philo[i].m_eating, DESTROY);
	free(data->philo);
	i = -1;
	while (++i < data->philo_nb)
		safe_mutex_handle(&data->m_forks[i], DESTROY);
	free(data->m_forks);
	safe_mutex_handle(&data->m_print, DESTROY);
	safe_mutex_handle(&data->m_finish, DESTROY);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv))
		return (1);
	if (init_all(&data, argv))
		return (1);
	if (start_threads(&data))
		return (1);
	free_all(&data);
	return (0);
}
