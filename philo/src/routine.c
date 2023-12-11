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
 * 1) First philo starts routine, every next one (2, 4, 6, etc.) will wait
 * 1.1) If theres and odd number of philosophers, last one must wait 2 wait cycles WHY?
*/
void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (philo->lll)
}