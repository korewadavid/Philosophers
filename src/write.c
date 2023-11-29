/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:21 by damendez          #+#    #+#             */
/*   Updated: 2023/11/29 16:08:21 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * [time in ms] [philo_id] [action]
 * 
 * thread safe, we need a lock so only one message appears at a time
*/

void    write_status(t_philo_status status, t_philo *philo)
{
    long    elapsed;

    elapsed = gettime(MILLISECOND) - philo->data->start_time;
    safe_mutex_handle(&philo->data->write_mutex, LOCK);
    if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) 
        && !simulation_finished(philo->data))
        printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
    safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}