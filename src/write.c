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
 * writes philo status in a thread safe way
 * 
 * 1) if philo is full return
 * 2) debig version (?)
 * 3) write status sent to function
*/

void    write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long    elapsed;

    elapsed = gettime(MICROSECOND) - philo->data->start_time;

    if (philo->full)
        return ;
    safe_mutex_handle(&philo->data->write_mutex, LOCK)
    {
        if (debug) // TO-DO
            write_status_debug(status, philo, elapsed);
        else
        {
            if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
        }
    }
}