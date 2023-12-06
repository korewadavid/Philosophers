/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/12/05 19:17:52 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		safe_mutex_handle(&data->philos[i].philo_mutex, DESTROY);
	free(data->philos);
	i = -1;
	while (++i < data->philo_nbr)
		safe_mutex_handle(&data->forks[i], DESTROY);
	free(data->forks);
	safe_mutex_handle(&data->data_mutex, DESTROY);
	safe_mutex_handle(&data->write_mutex, DESTROY);
}

int main(int argc, char **argv)
{
	t_data data;

	if (check_input(argc, argv))
		return (1);
	if (init_program(argc, argv))// TO-DO
		return (1);
	if (start_program(argc, argv))// TO-DO
		return (1);
	free_all(&data);
	return (0);
}
