/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:08:49 by damendez          #+#    #+#             */
/*   Updated: 2023/11/28 18:08:49 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Getters and setters used to avoid writing LOCK and UNLOCK everywhere
*/

// BOOL
void    set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

bool    get_bool(pthread_mutex_t *mutex, bool *value)
{
    bool ret;

    safe_mutex_handle(mutex, LOCK);
    // READING thread safe
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}

// LONG
void    set_long(pthread_mutex_t *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

long    get_long(pthread_mutex_t *mutex, long *value)
{
    long ret;

    safe_mutex_handle(mutex, LOCK);
    // READING thread safe
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}

bool    simulation_finished(t_data *data)
{
    return (get_bool(&data->data_mutex, &data->end_simulation))
}