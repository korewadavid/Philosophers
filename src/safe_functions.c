/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:20:57 by damendez          #+#    #+#             */
/*   Updated: 2023/11/27 15:47:03 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	Functions with embedded checks to errors	
*/

void    *safe_malloc(size_t bytes)
{
    void    *ret;

    ret = malloc(bytes);
    if (ret == NULL)
        error_exit(ALLOC_ERR);
    return (ret);
}

/*
 *	Handling Errors:
 *	On success, mutex and thread functions return 0
 *	else, an error number (errno.h) is returned indicating the error
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
        error_exit("The current thread already owns the mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit("Insufficient memory exists to initialize the mutex.");
	else if (status == EBUSY)
		error_exit("Mutex is locked.")
}

static void handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("Insufficient resources to create another thread.");
	else if (status == EPERM)
		error_exit("The caller does not have appropiate permission.");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable.");
	else if (status == ESRCH)
		error_exit("No thread with the ID specified could be found");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected (e.g., two threads tried to join
              with each other); or thread specifies the calling thread.");
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
        error_exit("Invalid opcode for mutex_handle, use <LOCK> <UNLOCK> <INIT> <DESTROY>");
}

void	safe_thread_handle(pthread_t *thread, void *(*start_routine)(void *), void *arg, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, start_routine, arg), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Invalid opcode for thread_handle, use <CREATE> <JOIN> <DETACH>");
}
