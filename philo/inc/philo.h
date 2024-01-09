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

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					r_fork;
	int					l_fork;
	t_data				*data;
	int					meals_done;
	unsigned long		last_meal_t;
	int					eating;
	pthread_mutex_t		m_eating;
}			t_philo;

typedef struct s_data
{
	int				philo_nb;
	unsigned long	die_t;
	unsigned long	eat_t;
	unsigned long	sleep_t;
	int				meals;
	unsigned long	start_t;
	t_philo			*philo;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_print;
	bool			finish;
	pthread_mutex_t	m_finish;
}			t_data;

/*	 	time.c		*/
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);

/*		errors.c	*/
int				input_ok(int ac, char **av);

/*		utils.c		*/
long int		ft_atol(char *str);
int				ft_isdigit(int c);

/*		init.c		*/
int				init_all(t_data *data, char **av);

/*		actions.c	*/
void			*philo_routine(void *arg);

/*		print.c		*/
void			ft_print(t_philo *philo, char *str);
void			ft_print_died(t_philo *philo, char *str);

/*		checker.c	*/
void			*go_on(void *arg);

#endif