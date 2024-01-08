/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:57:58 by damendez          #+#    #+#             */
/*   Updated: 2023/12/20 17:31:55 by damendez         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->m_forks[philo->l_fork]);
	ft_print(philo, "has taken a fork");
	// while (1)
	// {
	// 	if (philo->data->finish == true)
	// 		return (NULL);
	// }
	ft_usleep(philo->data->die_t);
	pthread_mutex_unlock(&philo->data->m_forks[philo->l_fork]);
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
	philos_th = malloc(sizeof(pthread_t) * data->philo_nb);
	if (!philos_th)
		return (1);
	if (data->philo_nb == 1)
	{
		data->start_t = get_time();
		if (pthread_create(&philos_th[0], NULL, case_one_philo, &data->philos[0]) != 0)
			return (1);
	}
	else
	{
		data->start_t = get_time();
		while (++i < data->philo_nb)
		{
			if (pthread_create(&philos_th[i], NULL, philo_routine, &data->philos[i]) != 0)
				return (1);
		}
	}
	if (pthread_create(&monitor, NULL, monitor_routine, &data) != 0)
		return (1);
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_join(philos_th[i], NULL) != 0)
			return (1);
	}
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	free(philos_th);
	return (0);
}

static void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->philos[i].m_eating);
	free(data->philos);
	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->m_forks[i])
	free(data->m_forks);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_finish)
}

int main(int argc, char **argv)
{
	t_data data;

	if (check_input(argc, argv))
		return (1);
	if (init_all(&data, argv))
		return (1);
	if (start_routines(&data))
		return (1);
	// if (free_all(&data))
	// 	return (1);
	free_all(&data);
	return (0);
}
