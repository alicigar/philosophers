/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:25:44 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/08 22:24:55 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_data *data, int i)
{
	long	current_time;
	long	last_meal_copy;
	long	time_since_meal;

	current_time = get_time();
	pthread_mutex_lock(&data->log_mutex);
	last_meal_copy = data->philos[i].last_meal;
	pthread_mutex_unlock(&data->log_mutex);
	time_since_meal = current_time - last_meal_copy;
	if (time_since_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d died\n", current_time - data->start_time, \
data->philos[i].id);
		pthread_mutex_unlock(&data->log_mutex);
		pthread_mutex_lock(&data->death_mutex);
		data->dead = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	meals_copy;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->log_mutex);
		meals_copy = data->philos[i].meals;
		pthread_mutex_unlock(&data->log_mutex);
		if (meals_copy < data->must_eat)
			return (0);
		i++;
	}
	pthread_mutex_lock(&data->death_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->death_mutex);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			i++;
		}
		if (check_all_ate(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
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
