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
/*
 * If only 1 philo, monitor will not be used, thread just does nothing for die_t then returns null
*/
static void	*case_one_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	safe_mutex_handle(&philo->data->m_forks[philo->l_fork], LOCK);
	ft_print(philo, "has taken a fork");
	// while (1)
	// {
	// 	if (philo->data->finish == true)
	// 		return (NULL);
	// }
	ft_usleep(philo->data->die_t);
	safe_mutex_handle(&philo->data->m_forks[philo->l_fork], UNLOCK);
	return (NULL);
}

/*
 * 1) Safe allocate memory for array of thread identifiers for philo threads
 * 2) If only 1 philo, create philo thread invoking case_one_philo()
 * 2.1) If philos > 1, create threads invoking philo_routine()
 * 3) Create monitor thread that constantly checks if a philo has 
 * died or if they have all finished eating, either one will finish the program
 * 4) wait for threads to terminate, on success free thread id array
*/
static int	start_routines(t_data *data)
{
	pthread_t	*philos_th;
	pthread_t	monitor;
	int			i;

	i = -1;
	philos_th = safe_malloc(sizeof(pthread_t) * data->philo_nb);
	data->start_t = get_time(); // DIFFERENT
	if (data->philo_nb == 1)
		safe_thread_handle(&philos_th[0], case_one_philo, &data->philos[0], CREATE);
	else
	{
		while (++i < data->philo_nb)
			safe_thread_handle(&philos_th[i], philo_routine, &data->philos[i], CREATE);
	}
	safe_thread_handle(&monitor, monitor_routine, &data, CREATE);
	i = -1;
	while (++i < data->philo_nb)
		safe_thread_handle(&philos_th[i], NULL, NULL, JOIN);
	free(philos_th);
	return (0);
}

static void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		safe_mutex_handle(&data->philos[i].m_eating, DESTROY);
	free(data->philos);
	i = -1;
	while (++i < data->philo_nb)
		safe_mutex_handle(&data->m_forks[i], DESTROY);
	free(data->m_forks);
	safe_mutex_handle(&data->m_print, DESTROY);
	safe_mutex_handle(&data->m_finish, DESTROY);
}

int main(int argc, char **argv)
{
	t_data data;

	if (check_input(argc, argv))
		return (1);
	if (init_all(&data, argv))
		return (1);
	if (start_routines(argc, argv))
		return (1);
	free_all(&data);
	return (0);
}
