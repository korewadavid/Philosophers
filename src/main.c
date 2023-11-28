/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/11/22 17:15:47 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	ft_exit(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destory(&data->philos[i].lock);
	}
	pthread_mutex_destory(&data->lock);
	pthread_mutex_destory(&data->write);
	clear_data(&data);
}

int	error(char *err, t_data *data)
{
	printf("%s\n", err);
	if (data)
		ft_exit(data);
	return (1);
}

int main(int argc, char **argv)
{
	t_data data;
	
	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		init_data(&data);
		start_routine(&data);
		ft_clean(&data);
	}
	else
		error(ERR_IN_1);
	return (0);
}
