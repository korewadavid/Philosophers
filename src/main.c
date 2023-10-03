/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/10/03 15:57:58 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_arg_ifnum(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] >= '0' && arg[i] <= '9')
            i++;
        else
            return (1);
    }
    return (0);
}

int check_valid_args(char **argv)
{
    if (ft_atoi(argv[1]) > MAX_NUM_PHILO || ft_atoi(argv[1]) <= 0
            || check_arg_ifnum(argv[1]) == 1)
            return (write(2, "Invalid number_of_philosophers\n", 32), 1);
    if (ft_atoi(argv[2]) <= 0 || check_arg_ifnum(argv[2]) == 1)
        return (write(2, "Invalid time_to_die\n", 21), 1);
    if (ft_atoi(argv[3]) <= 0 || check_arg_ifnum(argv[3]) == 1)
        return (write(2, "Invalid time_to_eat\n", 21), 1);
    if (ft_atoi(argv[4]) <= 0 || check_arg_ifnum(argv[4]) == 1)
        return (write(2, "Invalid time_to_sleep\n", 23), 1);
    if (argv[5] && (ft_atoi(argv[4]) <= 0 || check_arg_ifnum(argv[4]) == 1))
        return (write(2, "Invalid number_of_times_each_philosopher_must_eat\n", 51), 1);
    return (0);
}

int main(int argc, char **argv)
{
    // 1. Check valid input
    if (argc != 5 && argc != 6)
        return (write(2, "Invalid argument count\n", 24), 1);
    if (check_valid_args(argv) == 1)
        return (1);
}