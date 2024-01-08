/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:21:15 by damendez          #+#    #+#             */
/*   Updated: 2023/12/05 20:19:50 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int error_exit(const char *error)
{
    printf("%s\n", error);
    return (1);
}

/*
 * 1) Skip leading whitespaces in the input string.
 * 2) Check for number sign and update variable
 * 3) Handle the case where the input string is empty after removing whitespaces.
 * 4) Iterate through the string while the characters are digits.
 * updating ret adding current char as an int
*/
long int    ft_atol(char *str)
{
    long int    res;
    long int    sign;
    long int    i;

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
	
    while (ft_isdigit((int)str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}