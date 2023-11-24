/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:20:57 by damendez          #+#    #+#             */
/*   Updated: 2023/11/23 17:20:57 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Functions with embedded controls on return
*/

void    *safe_malloc(size_t bytes)
{
    void    *ret;

    ret = malloc(bytes);
    if (ret == NULL)
        error_exit(ALLOC_ERR);
    return (ret);
}

// *** Mutex Safe ***
/*
    init
    destoy
    lock
    unlock
*/

static void handle_mutex_error(int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK || opcode == DESTORY))
        error_exit("The value specified by mutex is invalid.");
    else if (status == EINVAL && opcode == INIT)
        error_exit("The value specified by attr is invalid.");
    else if (status == EDEADLK)
        error_exit("")
}

void    safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
    if (opcode == LOCK)
        handle_mutex_error(pthread_mutex_lock(mutex), opcode);
    else if (opcode == UNLOCK)
        handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
    else if (opcode == INIT)
        handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
    else if (opcode == DESTROY)
        handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
    else
        error_exit(OP_MUTEX_ERR);
}