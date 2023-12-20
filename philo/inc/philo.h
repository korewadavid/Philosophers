/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:00:36 by damendez          #+#    #+#             */
/*   Updated: 2023/12/20 17:48:42 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Changes
 * 1) Change 'eating' fflag to bool
 * 2) Return (1) on error, 0 on success
 * 3) Make one_philo case creating a thread for the philo
 * 3.1) Instead of being called from main, it will be done from 'start routines'
 * 4) start_t initiated in start_routines()
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
	int					id;
	int					l_fork;
	int					r_fork;
	int					meals_done;
	bool				eating; 
	unsigned long		last_meal_t;
	pthread_mutex_t		m_eating;
	t_data				*data;
}			t_philo;

typedef struct s_data
{
	int				philo_nb;
	int				meals_nb;
	unsigned long	die_t;
	unsigned long	eat_t;
	unsigned long	sleep_t;
	unsigned long	start_t;
	bool			finish;
	pthread_mutex_t	m_finish;
	pthread_mutex_t	m_print;
	pthread_mutex_t	*m_forks;
	t_philo			*philos;
}			t_data;

/*	 	time.c		*/
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);

/*		input.c		*/
int				check_input(int argc, char **argv);

/*		utils.c		*/
long int		ft_atol(char *str);
bool			ft_isdigit(int c);
int 			error_exit(const char *error);

/*		init.c		*/
int				init_all(t_data *data, char **argv);

/*		routine.c	*/
void			*philo_routine(void *arg);

/*		write.c		*/
void			ft_print(t_philo *philo, char *str);
void			ft_print_died(t_philo *philo, char *str);

/*		monitor.c	*/
void			*monitor_routine(void *arg); 


// safe_functions.c
//int    safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
//int	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
//int	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
//int	*safe_malloc(size_t bytes);

#endif
