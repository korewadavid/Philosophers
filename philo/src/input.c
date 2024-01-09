/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:36:32 by damendez          #+#    #+#             */
/*   Updated: 2023/12/20 17:46:30 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_nb_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Input should be: ./philo + 4 or 5 args\n");
		return (0);
	}
	return (1);
}

/*
 * 1) For each input argument string after first one, check if the characters are digits
 * 1.1) If user gave 'meals_nb' check that its greater than 0
*/
static int	check_all_dig(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		while (av[i][j])
		{
			if (!ft_isdigit((int)av[i][j]) || (ac == 6 && ft_atol(av[5]) <= 0))
			{
				printf("All values after ./philo must be integers > 0\n");
				return (0);
			}
			else
				j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

/*
 * starting from time_to_die until last time value, 
 * check if string value (ft_atol) is less than 60ms
*/
static int	least_60(char **av)
{
	long	i;

	i = 2;
	while (i < 5)
	{
		if (ft_atol(av[i]) < 60)
		{
			printf("All times must be >= 60\n");
			return (0);
		}
		else
			i++;
	}
	return (1);
}

/*
 * 1) Check number of input arguments
 * 2) Check if format of input is correct (only digits)
 * 		ej: ./philo 5 800 200 200 [7]
 * 3) Check input values to see if their correct (timestamps and philo_nb)
*/
int	input_ok(int ac, char **av)
{
	long	n;

	if (!check_nb_args(ac) || !check_all_dig(ac, av) || !least_60(av))
		return (0);
	n = ft_atol(av[1]);
	if (n < 1 || n > 200)
	{
		printf("Number of philosophers should be 1-200\n");
		return (0);
	}
	return (1);
}
