/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:30:02 by damendez          #+#    #+#             */
/*   Updated: 2023/11/28 21:30:02 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Spinlock to synchronize philos start
void    wait_all_threads(t_data *data)
{
    while (!get_bool(&data->data_mutex, &data->all_threads_ready))
        ;
}