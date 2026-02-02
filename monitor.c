/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:25:44 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/02 20:33:42 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	current_time;
	long	time_since_meal;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			current_time = get_time();
			time_since_meal = current_time - data->philos[i].last_meal;
			if (time_since_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->log_mutex);
				printf("%ld %d died\n", current_time - data->start_time, \
data->philos[i].id);
				pthread_mutex_unlock(&data->log_mutex);
				pthread_mutex_lock(&data->death_mutex);
				data->dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int		i = 0;

	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philos[i].thread, NULL, \
philo_routine, &data->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, data);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
