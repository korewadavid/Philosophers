/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:36:32 by damendez          #+#    #+#             */
/*   Updated: 2024/01/31 21:09:09 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



static int	ft_isint(char *input)
{
	int		i;
	long	temp;

	i = 0;
	if (!input || !*input)
		return (1);
	if (input[i] == '-' || input[i] == '+'
		|| input[i] <= '0')
		return (error_msg("Incorrect input syntax\n", 1));
	if (ft_strlen(&input[i]) /*TO-DO*/ > ft_nbr_size(INT_MAX, 10)/*TO-DO*/) // Necessary?
		return (error_msg("Incorrect input value\n", 1));
	temp = ft_atol(input);
	if (temp < INT_MIN || temp > INT_MAX || temp < 60)
		return (error_msg("Incorrect input value\n", 1));
	return (0);
}

static int	ft_isnum(char *input)
{
	int	i;

	i = 0;
	if (!input || !*input)
		return (1);
	while (input[i])
	{
		if (input[i] < '0' || input[i] > '9')
			return (error_msg("Incorrect input value\n", 1));
		i++;
	}
	return (0);
}

/*
 * for each input arg string (argv[i]) we check if it is valid (0 < && >= INT_MAX)
*/
int	check_input(int argc, char **argv)
{
	int	i;
	
	if (argc < 5 || argc > 6)
		return (error_msg("Input should be: ./philo + 4 or 5 args\n", 1));
	i = -1;
	while (++i < (argc - 1))
		if (ft_isint(argv[i]) /* TO-DO */ || ft_isnum(argv[i]))
			return (error_msg("All values after ./philo must be integers > 0 less then INT_MAX\n", 1));
	return (0);
}
