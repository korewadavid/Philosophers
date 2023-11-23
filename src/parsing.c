/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:03:05 by damendez          #+#    #+#             */
/*   Updated: 2023/11/22 17:52:09 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/*
 * 1. check for negatives
 * 2. check if number is legit
 * 			"		+29$%" is ok
 * 			"		+&%42" is NOT ok
 * 3. Do first check for input being > INT_MAX
 * 4. We return pointer of where we want to start ft_atol:
 * 			"		+29&$"
 * 					 ↑ pointer
*/
static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error(ERR_IN_1, NULL);
	if (!is_digit(*str))
		error(ERR_IN_1, NULL);
	number = str; // now return pointer is pointing to the first input digit
	while (is_digit(*str++))
		++len;
	// check INT_MAX
	if (len > 10)
		error(ERR_IN_2, NULL);
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error(ERR_IN_2, NULL);
	return (num); 
}

/*                    ms      ms    ms
 * ./philo   5       800     200   200   [4]
 *        argv[1]  argv[2]  ...
 * 1. check if input are actual numbers
 * 2. Check INT_MAX overflow
 * 3. timestamps > 60ms ?
 * user gives times in miliseconds, but usleep wants microseconds,
 * 1 ms = 100
 */
int	parse_input(t_data *data, char **argv)
{
	data->philo_num = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		data->nbr_max_meals = ft_atol(argv[5]);
	else
		data->nbr_max_meals = -1;
	return (0);
}
