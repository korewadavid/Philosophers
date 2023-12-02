/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:28:22 by damendez          #+#    #+#             */
/*   Updated: 2023/11/30 17:13:03 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TO-DO (time to think we can model, other times are fixed from input)
static void thinking(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
}

/*
 * similar to routine_simulation
 * 
 * 1) fake lock the fork
 * 2) sleep until the monitor will bust it
*/
void    *lone_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    wait_all_threads(philo->data);
    set_long(philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECONDS));
    increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    while (!simulation_finished(philo->data))
        usleep(200);
    return (NULL);
}

/*
 * eat routine
 * 
 * 1) grab the forks (first and second)
 * 2) eat: write eat, update last meal time, updeat meal_counter
 *      eventually change the status of bool full
 * 3) release the forks
*/
static void eat(t_philo *philo)
{
    // 1)
    safe_mutex_handle(philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

    // 2)
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    philo->eat_count++;
    write_status(EATING, philo, DEBUG_MODE); // TO-DO
    precise_usleep(philo->data->time_to_eat, philo->data);
    // Internal check see if philo is full
    if (philo->data->nbr_max_meals > 0 
        && philo->eat_count == philo->data->nbr_max_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    
    // 3)
    safe_mutex_handle(&philo->first_fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork, UNLOCK);
}

/*
 * 0) wait all philos, synchro start
 * 1) endless loop philo
*/
void    *routine_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    // spinlock: the threads will loop/wait until the all_threads_ready flag is set to true 
    wait_all_threads(philo->data);

    // set last meal time
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    
    // update threads_running_nbr so the monitor knows when to start
    increase_long(&philo->data->data_mutex, 
            &philo->data->threads_running_nbr);
    
    while (!simulation_finished(philo->data))
    {
        // 1) Check if philo is full
        if (philo->full) // TO-DO, might have to protect with mutex
            break;
        
        // 2) eat
        eat(philo);

        // 3) sleep -> write_status (TO-DO) and precise_usleep
		write_status(SLEEPING, philo, DEBUG_MODE); // TO-DO
        precise_usleep(philo->data->time_to_sleep, philo->data);

        // 4) think
        thinking(philo)
    }
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
        safe_thread_handle(&data->philos[0].thread_id, lone_philo, &data->philos[0], CREATE);
    else
    {
        while (++i < data->philo_nbr)
            safe_thread_handle(&data->philos[i].thread_id, routine_simulation, &data->philos[i], CREATE);
    }
    safe_thread_handle(&data->monitor, monitor_routine, data, CREATE);
    data->start_time = gettime(MILLISECOND);
    set_bool(&data->data_mutex, &data->all_threads_ready, true); 
    i = -1;
    while (++i < data->philo_nbr)
        safe_thread_handle(&data->philos[i].thread_id, NULL, NULL, JOIN);
    set_bool(&data->data_mutex, &data->end_simulation, true)
    safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
}
