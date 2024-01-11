/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:21:15 by damendez          #+#    #+#             */
/*   Updated: 2024/01/10 13:35:07 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
 * 1) Skip leading whitespaces in the input string.
 * 2) Check for number sign and update variable
 * 3) Handle the case where the input string is empty after removing whitespaces.
 * 4) Iterate through the string while the characters are digits.
 * updating ret adding current char as an int
*/
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
	while (ft_isdigit((int)str[i]) != 0)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}
