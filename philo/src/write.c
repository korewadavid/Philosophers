/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:21 by damendez          #+#    #+#             */
/*   Updated: 2024/01/31 18:43:16 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 * thread protected printf writing current timestamp in simulation, 
 * philo id and string we want to output 
*/
int	ft_print(t_philo *philo, char *str)
{
	long	time;

	time = time_now(philo);
	if (check_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->data->m_print);
	printf("%lu\t%d\t%s\n", time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->data->m_print);
	return (0);
}

int	error_msg(char *msg, int ret)
{
	printf("%s\n", msg);
	return (ret);
}
