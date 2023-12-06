/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:36:32 by damendez          #+#    #+#             */
/*   Updated: 2023/12/06 15:36:32 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// edc
#include "../inc/philo.h"

static inline bool	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

long int	ft_atol(char *str)
{
	long int	res;
	long int	sign;
	long int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	while (isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

static int	check_if_digits(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j]) || (argc == 6 && ft_atol(argv[5]) <= 0))
                error_exit("All values after ./philo must be integers > 0\n");
			else
				j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

static int	least_60(char **argv)
{
	long	i;

	i = 2;
	while (i < 5)
	{
		if (ft_atol(argv[i]) < 60)
            error_exit("All times must be >= 60\n");
		else
			i++;
	}
	return (0);
}

int check_input(int argc, char **argv)
{
    long n;

    if (argc < 5 || argc > 6)
        error_exit("Input should be: ./philo + 4 or 5 args\n")
	if (check_if_digits(argc, argv) || least_60(argv))
		return (1);
	n = ft_atol(av[1]);
	if (n < 1 || n > 200)
        error_exit("Number of philosophers should be 1-200\n");
	return (0);
}