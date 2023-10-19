/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/10/19 16:49:52 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_valid_args(char **argv) // iterates through input checking for non numeric values in input
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ') // let the spaces slide
			{
				j++;
				continue;
			}
			if (str[i][j] < 48 || str[i][j] > 57)
				return (error(ERR_IN_1, NULL); // error msg -> INVALID INPUT CHARACTER
			j++;
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data		data;

    // 1. Check valid input
    if (argc != 5 && argc != 6)
        return (write(2, "Invalid argument count\n", 24), 1);

    if (check_valid_args(argv))
        return (1);

    // 2. Initialize program
    if (init_program(&data, argv, argc));
}

/*
    Questions
    1. What is a mutex/pthread_mutex_t? 
    A mutex is like a lock which only allows the thread its locked on to by the lock owner to be executed.
*/

/*
    The Dining Philosophers Problem

    threads = the philosophers: a sequence stream within a process (lightweight process)
    ex: in a browser, multiple tabs can be different threads
    we will use a multithreading solution: 
*/
