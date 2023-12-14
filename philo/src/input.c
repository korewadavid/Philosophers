/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:36:32 by damendez          #+#    #+#             */
/*   Updated: 2023/12/14 14:31:05 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_argc(int argc)
{
	if (argc != 5 && argc != 6)
		error_exit("Invalid number of imput arguments. ej: ./philo 5 800 200 200 [7]");
	return (0);
}

/*
 * 1) For each input argument string after first one, check if the characters are digits
 * 1.1) If user gave 'meals_nb' check that its greater than 0
*/
static int	check_format(int argc, char **argv)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (++i < argc)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit((int)argv[i][j]))
				error_exit("All values after ./philo must be integers > 0\n");
			else
				j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

/*
 * starting from time_to_die until last time value, 
 * check if string value (ft_atol) is less than 60ms
*/
static int	check_time_values(char **argv)
{
	long	i;

	i = 1;
	while (++i < 5)
	{
		if (ft_atol(argv[i]) < 60)
			error_exit("All times must be >= 60\n");
	}
	return (0);
}

/*
 * 1) Check number of input arguments
 * 2) Check if format of input is correct (only digits)
 * 		ej: ./philo 5 800 200 200 [7]
 * 3) Check input values to see if their correct (timestamps and philo_nb)
*/
int check_input(int argc, char **argv)
{
	long n;

	if (check_argc(argc) || check_format(argc, argv) || check_time_values(argv))
		return (1);
	n = ft_atol(argv[1]);
	if (n < 1 || n > 200)
		error_exit("number_of_philosophers should be between 1 and 200");
	return (0);
}
