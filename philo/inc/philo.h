/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:00:36 by damendez          #+#    #+#             */
/*   Updated: 2023/12/05 20:20:06 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Changes
 *
 * 1) Implementation of safe functions
 * 2) One_philo case must be a thread (pthread_detach case)
 * 3) free_all doesnt seem to free philo mutexs, might need to be corrected
 * TO-DO 4) Return 1 on error, 0 on success
 * TO-DO 5) use of geters and seters ?
 * TO-DO 6) t_philo eatingflag change to bool
 * TO-DO 7) is_digit changed to bool
*/
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

/*
 * Enum for safe mutex and thread handle functions
*/
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}					t_opcode;

// *** STRUCTS ***

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				r_fork;
	int				l_fork;
	int				eat_count;
	bool			eating;
	unsigned long	last_meal_time;
	pthread_mutex_t	eating_mutex;
	t_data			*data;
}				t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				nbr_max_meals;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	start_time;
	bool			end_simulation; // if a philo dies or philos are full
	pthread_mutex_t print_mutex; // avoid race conditions when reading from data
	pthread_mutex_t finish_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}				t_data;

// *** Prototypes ***

// time.c
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);

// input.c
int				check_input(int argc, char **argv);

// utils.c
long int		ft_atol(char *str);
bool			ft_isdigit(int c);

// init.c
int				init_program(t_data *data, char **argv);

// routine.c
void			*routine(void *arg);

// write.c
void			ft_print(t_philo *philo, char *str);
void			ft_print_died(t_philo *philo, char *str);

// monitor.c
void			*monitor_routine(void *arg);

// safe_functions.c
void    safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	*safe_malloc(size_t bytes);

// get_set.c



//void	parse_input(t_data *data, char **argv);
//void	init_data(t_data *data);
//void    start_routine(t_data *data);
//void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
//bool	get_bool(pthread_mutex_t *mutex, bool *value);
// long	get_long(pthread_mutex_t *mutex, long *value);
// void	set_long(pthread_mutex_t *mutex, long *dest, long value);
//bool	simulation_finished(t_data *data);
// long    gettime(t_time_code time_code);
// void	precise_usleep(long usec);
// void	ft_clean(t_data *data);
// void	error_exit(const char *error);
// void	write_status(t_philo_status status, t_philo *philo, bool debug);
// void	wait_all_threads(t_data *data);
// void	increase_long(pthread_mutex_t *mutex, long *value);
//bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
// void    thinking(t_philo *philo, bool pre_simulation);
// void    de_synchronize_philos(t_philo *philo);
// void	*monitor_routine(void *edata);

#endif
