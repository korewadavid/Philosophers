/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:28:22 by damendez          #+#    #+#             */
/*   Updated: 2023/12/05 20:16:34 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// TO-DO (time to think we can model, other times are fixed from input)
/*
 * 
*/
// void thinking(t_philo *philo, bool pre_simulation)
// {
// 	long	t_eat;
// 	long	t_sleep;
// 	long	t_think;

// 	if (!pre_simulation)
// 		write_status(THINKING, philo, DEBUG_MODE);
// 	if (philo->data->philo_nbr % 2 == 0)
// 		return ;
// 	t_eat = philo->data->time_to_eat;
// 	t_sleep = philo->data->time_to_sleep;
// 	t_think = (t_eat * 2) - t_sleep;
// 	if (t_think < 0)
// 		t_think = 0;
// 	precise_usleep(t_think * 0.42);
	
// }

static void	sleep_think(t_philo *philo)
{
	if (simulation_finished(philo->data))
		return ;
	write_status(SLEEPING, philo, DEBUG_MODE);
	precise_usleep(philo->data->time_to_sleep);
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
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    // while (!simulation_finished(philo->data))
    //     precise_usleep(200);
    precise_usleep(philo->data->time_to_die);
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
    if (simulation_finished(philo->data))
		return ;
    safe_mutex_handle(&philo->data->forks[philo->l_fork], LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    safe_mutex_handle(&philo->data->forks[philo->r_fork], LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

    // 2)
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    increase_long(&philo->philo_mutex, &philo->eat_count); // DIFERENT FROM ANSWER
    set_bool(&philo->philo_mutex, &philo->eating, true);
    write_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->data->time_to_eat);
    set_bool(&philo->philo_mutex, &philo->eating, false);
    if (philo->data->nbr_max_meals > 0 
        && philo->eat_count == philo->data->nbr_max_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    
    // 3)
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/*
 * 0) wait all philos, synchro start
 * 1) endless loop philo
 *
 *
*/
void    *routine_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    wait_all_threads(philo->data);
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    increase_long(&philo->data->data_mutex, 
            &philo->data->threads_running_nbr);
    if (philo->philo_id % 2 == 0)
		precise_usleep(philo->data->time_to_eat / 2);
	else if (philo->data->philo_nbr % 2 != 0
		&& philo->philo_id == philo->data->philo_nbr)
		precise_usleep(philo->data->time_to_eat + 10);
    while (!simulation_finished(philo->data))
    {
        // 1) Check if philo is full
        //if (get_bool(&philo->philo_mutex, &philo->full))
           // break ;
        // 2) eat
        eat(philo);
        // 3) sleep
		//write_status(SLEEPING, philo, DEBUG_MODE);
        //precise_usleep(philo->data->time_to_sleep, philo->data);
        // 4) think
        //thinking(philo, false);
		sleep_think(philo);
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
 *
 * ft_launch
 * 0) Allocates space for a string of philosopher data types for each philosopher thread
 * 1) For each philosopher, a thread is started invoking 'actions'
 * 2) 
*/
int    start_routines(t_data *data)
{
    pthread_t   monitor;
    int         i;
    pthread_t   *philo_th;

    i = -1;
    philo_th = (pthread_t *)malloc(sizeof(pthread_t) * data->philo_nbr);
    if (data->nbr_max_meals == 0)
        error_exit("Invalid number_of_times_each_philosopher_must_eat\n");
    else if (data->philo_nbr == 1)
        safe_thread_handle(&philo_th[0], lone_philo, &data->philos[0], CREATE);
    else
    {
        while (++i < data->philo_nbr)
            safe_thread_handle(&philo_th[i], routine_simulation, &data->philos[i], CREATE);
    }
    safe_thread_handle(&monitor, monitor_routine, data, CREATE);
    data->start_time = gettime(MILLISECOND);
    set_bool(&data->data_mutex, &data->all_threads_ready, true); 
    i = -1;
    while (++i < data->philo_nbr)
        safe_thread_handle(&data->philo_th[i], NULL, NULL, JOIN);
    set_bool(&data->data_mutex, &data->end_simulation, true);
    safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
    free(philo_th);
    return (0);
}
