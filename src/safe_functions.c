/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:20:57 by damendez          #+#    #+#             */
/*   Updated: 2023/11/23 17:20:57 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Functions with embedded controls on return
*/

void    *safe_malloc(size_t bytes)
{
    void    *ret;

    ret = malloc(bytes);
    if (ret == NULL)
        error_exit(ALLOC_ERR);
    return (ret);
}

// *** Mutex 