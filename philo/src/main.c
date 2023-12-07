/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/12/05 19:17:52 by damendez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	case_one_philo(t_philo *philo)
{
	pthread_t	philo_th;

	data->start_time = get_time();
	safe_thread_handle(&philo_th, &routine, &data->philo[0], CREATE);
	pthread_detach(&philo_th);
	ft_usleep(philo->data->time_to_die);
	ft_print_died(philo->data->philo, "died");
	return (0);
}

static int	start_routines(t_data *data)
{
	pthread_t	monitor;
	int			i;
	pthread_t	*philo_th;
 
	i = -1;
	philo_th = safe_malloc(sizeof(pthread_t) * data->philo_nbr);
	while (++i < data->philo_nbr)
		safe_thread_handle(&philo_th[i], &routine, &data->philo[i], CREATE);
	safe_thread_handle(&monitor, &monitor_routine, data, CREATE);
	i = -1;
	while (++i < data->philo_nbr)
		safe_thread_handle(&philo_th[i], NULL, NULL, JOIN);
	safe_thread_handle(&monitor, NULL, NULL, JOIN);
	free(philo_th);
	return (0);
}

static void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		safe_mutex_handle(&data->philo[i].eating_mutex, DESTROY);
	free(data->philo);
	i = -1;
	while (++i < data->philo_nbr)
		safe_mutex_handle(&data->forks[i], DESTROY);
	free(data->forks);
	safe_mutex_handle(&data->print_mutex, DESTROY);
	safe_mutex_handle(&data->write_mutex, DESTROY);
}

int main(int argc, char **argv)
{
	t_data data;

	if (check_input(argc, argv))
		return (1);
	if (init_program(&data, argv))
		return (1);
	if (data.philo_nbr == 1)
		return (case_one_philo(data.philo))
	if (start_routines(argc, argv))// TO-DO
		return (1);
	free_all(&data);
	return (0);
}
