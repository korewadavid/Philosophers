/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:21 by damendez          #+#    #+#             */
/*   Updated: 2024/01/22 14:50:54 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 * thread protected printf writing current timestamp in simulation, 
 * philo id and string we want to output 
*/
void	ft_print(t_philo *philo, char *str)
{
	safe_mutex_handle(&philo->data->m_finish, LOCK);
	if (philo->data->finish == true)
	{
		safe_mutex_handle(&philo->data->m_finish, UNLOCK);
		return ;
	}
	safe_mutex_handle(&philo->data->m_finish, UNLOCK);
	safe_mutex_handle(&philo->data->m_print, LOCK);
	printf("%lu\t%d\t%s\n", get_time() - philo->data->start_t, philo->id, str);
	safe_mutex_handle(&philo->data->m_print, UNLOCK);
}

void	ft_print_died(t_philo *philo, char *str)
{
	safe_mutex_handle(&philo->data->m_print, LOCK);
	printf("%lu\t%d\t%s\n", get_time() - philo->data->start_t, philo->id, str);
	safe_mutex_handle(&philo->data->m_print, UNLOCK);
}
