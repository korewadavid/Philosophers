/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/12/20 17:31:55 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_launch(t_data *data)
{
	pthread_t	checker;
	int			i;
	pthread_t	*philo_th;

	i = -1;
	philo_th = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_nb);
	if (!philo_th)
		return (0);
	data->start_t = get_time();
	while (++i < data->philo_nb)
		if (pthread_create(&philo_th[i], NULL, &philo_routine, &data->philo[i]) != 0)
			return (0);
	if (pthread_create(&checker, NULL, &go_on, data) != 0)
		return (0);
	i = -1;
	while (++i < data->philo_nb)
		if (pthread_join(philo_th[i], NULL) != 0)
			return (0);
	if (pthread_join(checker, NULL) != 0)
		return (0);
	free(philo_th);
	return (1);
}

static void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->philo[i].m_eating);
	free(data->philo);
	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->m_forks[i]);
	free(data->m_forks);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_finish);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!input_ok(ac, av))
		return (0);
	if (!init_all(&data, av))
		return (0);
	if (!ft_launch(&data))
		return (0);
	free_all(&data);
	return (1);
}