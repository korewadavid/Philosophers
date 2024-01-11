/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:31:13 by damendez          #+#    #+#             */
/*   Updated: 2024/01/11 17:51:57 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void handle_error(int status)
{
    if (status != 0)
        exit(EXIT_FAILURE);
    return ;
}

void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_error(pthread_mutex_lock(mutex));
	else if (UNLOCK == opcode)
		handle_error(pthread_mutex_unlock(mutex));
	else if (INIT == opcode)
		handle_error(pthread_mutex_init(mutex, NULL));
	else if (DESTROY == opcode)
		handle_error(pthread_mutex_destroy(mutex));
	else
        exit(EXIT_FAILURE);
}

void    safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
    if (CREATE == opcode)
        handle_error(pthread_create(thread, NULL, foo, data));
    else if (JOIN == opcode)
        handle_error(pthread_join(*thread, NULL));
    else if (DETACH == opcode)
        handle_error(pthread_detach(*thread));
    else
        exit(EXIT_FAILURE);
}