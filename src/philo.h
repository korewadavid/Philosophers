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

# ifndef DEBUG_MODE
#	define DEBUG_MODE 0
# endif

# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

/*
 * Philosopher states for write
*/
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}					t_philo_status;

/*
 * Enum for safe mutex and thread handle functions
*/
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

/*
 * Units of time for gettime()
*/
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}					t_time_code;

/*
 * Colors for debug output
*/
# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

// *** STRUCTS ***

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id
}				t_fork;

typedef struct s_philo
{
	int				philo_id;
	long			eat_count;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex; // useful for race cond with the monitor thread
	t_data			*data;
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

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	*safe_malloc(size_t bytes);
void	parse_input(t_data *data, char **argv);
void	init_data(t_data *data);
void    start_routine(t_data *data);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	simulation_finished(t_data *data);
long    gettime(t_time_code time_code);
void	precise_usleep(long usec, t_data *data);
void	ft_clean(t_data *data);
void	error_exit(const char *error);
void	write_status(t_philo_status status, t_philo *philo, bool debug);
void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void    thinking(t_philo *philo, bool pre_simulation); // TO-DO
void    de_synchronize_philos(t_philo *philo); // TO-DO
void	*monitor(void *edata);

#endif
