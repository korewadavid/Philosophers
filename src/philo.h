/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:00:36 by damendez          #+#    #+#             */
/*   Updated: 2023/11/30 17:13:41 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h> // printf
#include <stdlib.h> // malloc free
#include <unistd.h> // write usleep
#include <stdbool.h> // bools
#include <pthread.h> // threads and mutex
#include <sys/time.h> //gettimeofday
#include <limits.h> // intmax overflow
#include <errno.h> // safe functions

# define ERR_IN_1 "Error Invalid Input Character"
# define ERR_IN_2 "Error Invalid Input Values"

# define OP_MUTEX_ERR "Wrong opcode for mutex handle"

# define ALLOC_ERR "Malloc error"
# define ALLOC_ERR_1 "Error while allocating: Thread IDs"
# define ALLOC_ERR_2 "Error while allocating: Forks"
# define ALLOC_ERR_3 "Error while allocating: Philos"

# define TH_ERR "Error while creating: Threads"
# define JOIN_ERR "Error while joining: Threads"

# define MAX_NUM_PHILO 200

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}					t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTORY,
	CREATE,
	JOIN,
	DETACH,
}					t_opcode;

// Codes for gettime()
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}					t_time_code;

// *** STRUCTS ***

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int fork_id
}				t_fork;

typedef struct s_philo
{
	int			philo_id;
	long		eat_count;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	pthread_mutex_t philo_mutex; // useful for race cond with the monitor thread
	t_data		*data;
}				t_philo;

// ./philo 5 800 200 200

struct s_data
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_max_meals;
	long			start_time;
	bool			end_simulation; // if a philo dies or philos are full
	bool			all_threads_ready; // for synchronizing th start of the philos
	long			threads_running_nbr;
	pthread_t		monitor;
	pthread_mutex_t data_mutex; // avoid race conditions when reading from data
	pthread_mutex_t write_mutex;
	t_fork			*forks;
	t_philo			*philos;
}				t_data;

// *** Prototypes ***

// *** parsing ***
void 

#endif
