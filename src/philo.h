/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:00:36 by damendez          #+#    #+#             */
/*   Updated: 2023/10/18 17:19:20 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <pthread.h> // threads library
#include <unistd.h> // write()
#include <stdio.h> //stdin/stdout/printf
#include <sys/time.h>

# define MAX_NUM_PHILO 200

typedef struct s_philo
{
	struct s_data	*data; // pointer to general data stucture
    pthread_t       thread;
    int             id;
	int				eat_count;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
    pthread_mutex_t *r_lock; // pointer to right forks mutex
    pthread_mutex_t *l_fork;
}               t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num; // number of philosophers
	int				meals_nb; // number of meals each philosopher is expected to eat
	int				dead;
	int				finished; // if all the philosophers have finished eating
	t_philo         *philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t lock;
	pthread_mutex_t	write; // controlls access to writing to the output
}               t_program;

#endif
