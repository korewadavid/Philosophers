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
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_check_dead, NULL))
	{
		pthread_mutex_destroy(&data->m_print);
		return (1);
	}
	if (pthread_mutex_init(&data->m_time, NULL))
	{
		pthread_mutex_destroy(&data->m_print);
		pthread_mutex_destroy(&data->m_check_dead);
		return (1);
	}
	if (pthread_mutex_init(&data->m_last_meal_time, NULL))
	{
		pthread_mutex_destroy(&data->m_print);
		pthread_mutex_destroy(&data->m_check_dead);
		pthread_mutex_destroy(&data->m_time);
		return (1);
	}
	while (++i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL))
		{
			while (--i > 0)
				pthread_mutex_destroy(&data->m_forks[i]);
			pthread_mutex_destroy(&data->m_print);
			pthread_mutex_destroy(&data->m_check_dead);
			pthread_mutex_destroy(&data->m_time);
			return (1);
		}
	}
	return (0);
}

static void	init_philos(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->philo_nb)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = i - 1;
		if (i == 0)
			data->philos[i].r_fork = data->philo_nb - 1;
		//data->philos[i].last_meal_time = get_time();
		data->philos[i].ph_meal = 0;
		data->philos[i].data = data;
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->dead = 0;
	data->is_print = 0;
	data->total_meals = 0;
	data->philo_nb = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->eat_time = ft_atol(argv[3]);
	data->sleep_time = ft_atol(argv[4]);
	data->must_eat_nb = -1;
	if (argc == 6)
		data->must_eat_nb = ft_atol(argv[5]);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (1);
	data->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->m_forks)
		return (ft_free(data->philos, NULL));
	if (init_mutex(data) == 1)
		return (ft_free(data->philos, data->m_forks));
	init_philos(data);
	return (0);
}