/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/11/17 17:24:32 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}
	// if allocated memory pointers in data struct are present, free() them

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
	// for each philosopher, eliminate forks and philo lock mutexs

	// eliminate the remaining mutexes in data struct

	// call clear_data

int	error(char *err, t_data *data)
{
	printf("%s\n", err);
	if (data)
		ft_exit(data);
	return (1);
}
	// Print error message

	// If data pointer was passed as paramter eliminate data stored

	// Return error value 1

int	check_input(int argc, char **argv)
{
	int i;
	int j;
	
	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == 32)
			{
				j++;
				continue;
			}
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (error(ERR_IN_1, NULL));
			j++;
		}
		i++;
	}
	return (0);
}
	// iterate thorugh argv

	// if there are spaces present skip to the next iteration of the loop
			
	// if the current char is not valid (not a number), return error

int main(int argc, char **argv)
{
	t_data data;
	
	if (argc < 5 || argc > 6)
		return (1);
	if (check_input(argc, argv));
		return (1);
	if (init_program(&data, argc, argv));
		return (1);
	if (data.philo_num == 1)
		return (case_one(&data));
	if (thread_init(&data));
		return (1);
	ft_exit(&data);
	return (0);
}
	// Declare data struct
	// Check if number of input arguments is correct
	// Check if user input is correct (philo_num, death_time, eat_time, sleept_time) and check optional fifth argument meals_num
	// Initiate program structures (here we also check if input values are correct)
	// Run specific code in the case of one philosopher
	// Initiate threads for philosophers
	// Exit program by clearing all data once finished
