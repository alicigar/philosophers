/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:42:37 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/13 18:38:57 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->dead = 0;
	data->start_time = get_time();
	pthread_mutex_init(&data->log_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->forks = NULL;
	data->philos = NULL;
	return (0);
}

int	init_forks(t_data *data)
{
	int		i;

	data->forks = malloc(sizeof(pthread_mutex_t) * \
data->number_of_philosophers);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].last_meal = get_time();
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->number_of_philosophers;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}

int	initialize_all(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv))
		return (1);
	if (init_forks(data))
	{
		cleanup(data);
		return (1);
	}
	if (init_philos(data))
	{
		cleanup(data);
		return (1);
	}
	return (0);
}
