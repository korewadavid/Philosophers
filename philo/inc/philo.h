/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:00:36 by damendez          #+#    #+#             */
/*   Updated: 2024/01/22 16:51:12 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

// typedef enum e_opcode
// {
// 	LOCK,
// 	UNLOCK,
// 	INIT,
// 	DESTROY,
// 	CREATE,
// 	JOIN,
// 	DETACH,
// }					t_opcode;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					philo_id;
	pthread_t			thread_id;
	int					r_fork;
	int					l_fork;
	unsigned long long	last_meal_time;
	int					ph_meal; // nb of times specific philo has aten
	t_data				*data;
}			t_philo;

typedef struct s_data
{
	int				philo_nb;
	unsigned long	time_to_die;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	int				must_eat_nb;
	int				philo_full;
	int				dead;
	int				is_print;
	int				total_meals;
	unsigned long	start_time;
	unsigned long	dead_time;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_check_dead;
	pthread_mutex_t	m_time;
	pthread_mutex_t	m_last_meal_time;
	t_philo			*philos;
}			t_data;

/*	 	time.c		*/
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);
unsigned long	time_now(t_philo *philo);
int				specific_usleep(t_philo *philo);

/*		input.c	*/
int				check_input(int argc, char **argv);

/*		utils.c		*/
long int		ft_atol(char *str);
int				ft_isdigit(int c);
int				check_dead(t_philo *philo);
int				ft_free(void *f1, void *f2);

/*		init.c		*/
int				init_data(t_data *data, int argc, char **argv);

/*		routine.c	*/
void			*philo_routine(void *arg);

/*		eat.c		*/
int				philo_eat(t_philo *philo);

/*		write.c		*/
int				ft_print(t_philo *philo, char *str);
int				error_msg(char *msg, int ret);

/*		monitor.c	*/
//void			*monitor_routine(void *arg); // TO_DO

/*		safe_func.c	*/
//void			safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode); // TO-DO
//void			safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode); // TO-DO

#endif