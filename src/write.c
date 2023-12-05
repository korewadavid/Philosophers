/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:21 by damendez          #+#    #+#             */
/*   Updated: 2023/12/05 19:49:52 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    if (TAKE_FIRST_FORK == status && !simulation_finished(philo->data))
		printf(W"%6ld"RST" %d has taken the 1° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->philo_id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->data))
		printf(W"%6ld"RST" %d has taken the 2° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->philo_id,
			philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->data))
		printf(W"%6ld"C" %d is eating 🍝"
			"\t\t\t"Y"[🍝 %ld 🍝]\n"RST, elapsed, philo->philo_id, philo->eat_count);
	else if (SLEEPING == status && !simulation_finished(philo->data))
		printf(W"%6ld"RST" %d is sleeping 😴\n", elapsed, philo->philo_id);
	else if (THINKING == status && !simulation_finished(philo->data))
		printf(W"%6ld"RST" %d is thinking 🤔\n", elapsed, philo->philo_id);
	else if (DIED == status)
		printf(RED"\t\t💀💀💀 %6ld %d died   💀💀💀\n"RST, elapsed, philo->philo_id);
}

/*
 * writes philo status in a thread safe way
 * 
 * 1) if philo is full, return
 * 2) debug version
 * 3) write status sent to function
*/
void    write_status(t_philo_status status, t_philo *philo, bool debug)
{
    long    elapsed;

    elapsed = gettime(MILLISECOND) - philo->data->start_time;
    if (get_bool(&philo->philo_mutex, &philo->full))
        return ;
    safe_mutex_handle(&philo->data->write_mutex, LOCK);
    if (debug) 
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
            && !simulation_finished(philo->data))
            printf("%-6ld %d has taken a fork\n", elapsed, philo->philo_id);
        else if (status == EATING && !simulation_finished(philo->data))
            printf("%-6ld %d is eating\n", elapsed, philo->philo_id);
        else if (status == SLEEPING && !simulation_finished(philo->data))
            printf("%-6ld %d is sleeping\n", elapsed, philo->philo_id);
        else if (status == THINKING && !simulation_finished(philo->data))
            printf("%-6ld %d is thinking\n", elapsed, philo->philo_id);
        else if (status == DIED)
            printf("%-6ld %d died\n", elapsed, philo->philo_id);
    }
    safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}
