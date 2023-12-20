/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:21 by damendez          #+#    #+#             */
/*   Updated: 2023/12/20 17:38:53 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 * thread protected printf writing current timestamp in simulation, philo id and string we want to output 
*/
void    ft_print(t_philo *philo, char *str)
{
    if (philo->data->finish == true)
        return ;
    pthread_mutex_lock(&philo->data->m_print);
    printf("%lu\t%d\t%s\n", get_time() - philo->data->start_t, philo->id, str);
    pthread_mutex_unlock(&philo->data->m_print);
}

void    ft_print_died(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->data->m_print);
    printf("%lu\t%d\t%s\n", get_time() - philo->data->start_t, philo->id, str);
    pthread_mutex_unlock(&philo->data->m_print);
}
