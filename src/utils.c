/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:21:15 by damendez          #+#    #+#             */
/*   Updated: 2023/12/04 15:18:24 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * gettimeofday
 * time_code -> philo.h enum
*/
long    gettime(t_time_code time_code)
{
    struct timeval  tv;

    if (gettimeofday(&tv, NULL))
        error_exit("Gettimeofday failed");
    if (time_code == SECOND)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (time_code == MILLISECOND)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (time_code == MICROSECOND)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input to gettime().");
    return (1);
}

/*
 * precise usleep, og one is inaccurate (can sleep more time then expected).
 * 
 * is the simulation finished?
 * 
 * 1) usleep the majority of the time
 * 2) last microseconds will be waited with spinlock
*/
void    precise_usleep(long usec, t_data *data)
{
    long start;
    long elapsed;
    long remaining;

    start = gettime(MICROSECOND);
    while (gettime(MICROSECOND) - start < usec)
    {
        if (simulation_finished(data))
            break ;
        elapsed = gettime(MICROSECOND) - start;
        remaining = usec - elapsed;
        if (remaining > 1e3)
            usleep(remaining / 2);
        else
        {
            while (gettime(MICROSECOND) - start < usec)
                ;
        }
    }
}

void    ft_clean(t_data *data)
{
    t_philo *philo;
    int     i;

    i = -1;
    while (++i < data->philo_nbr)
    {
        philo = data->philos + 1;
        safe_mutex_handle(&philo->philo_mutex, DESTROY);
    }
    safe_mutex_handle(&data->write_mutex, DESTROY);
    safe_mutex_handle(&data->data_mutex, DESTROY);
    free(data->forks);
    free(data->philos);
}

void    error_exit(const char *error)
{
    printf("%s\n", error);
    exit(EXIT_FAILURE);
}
