/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:46 by damendez          #+#    #+#             */
/*   Updated: 2023/12/14 17:25:46 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
 * Uses gettimeofday to get number of secs and microsecs since 1/1/1970 (unix time)
 * , converts secs and microsecs to millisecs
*/
unsigned long	get_time(void)
{
    struct timeval  tv;

    if (gettimeofday(&tv, NULL))
        return (0);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void			ft_usleep(unsigned long time)
{
    unsigned long   start;
    start = get_time();
    while ((get_time() - start) < time)
        usleep(200);
}
