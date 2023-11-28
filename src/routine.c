/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:28:22 by damendez          #+#    #+#             */
/*   Updated: 2023/11/28 16:28:22 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * 0) wait all philos, synchro start
 * 1) endless loop philo
*/

void    *routine_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    wait_all_threads(philo->data); // TO-DO
    return (NULL);
}

/*
 * ./philo 5 800 200 200 [5]
 * 0) If no meals: [0], just return to main
 * 0.1) If only one philo -> make function for this situation
 * 1) Create all threads, all philos
 * 2) Create a monitor thread -> checks when philos died
 * 3) Synchronize simulation start -> all philos start at the same time
 * 4) Join the philos to main when done (?)
*/
void    start_routine(t_data *data)
{
    int i;

    i = -1;
    if (data->nbr_max_meals == 0)
        return ;
    else if (data->philo_nbr == 1)
        ; // TODO
    else
    {
        while (++i < data->philo_nbr)
            safe_thread_handle(&data->philos[i].thread_id, routine_simulation, &data->philos[i], CREATE);
    }

    // now all threads are ready
    
}