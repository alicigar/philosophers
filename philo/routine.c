/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:03:48 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/16 14:00:10 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

void	philo_think(t_philo *philo)
{
	if (!check_death(philo->data))
	{
		pthread_mutex_lock(&philo->data->log_mutex);
		printf("%ld %d is thinking\n", get_time() - \
philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->log_mutex);
	}
}

void	philo_sleep(t_philo	*philo)
{
	if (!check_death(philo->data))
	{
		pthread_mutex_lock(&philo->data->log_mutex);
		printf("%ld %d is sleeping\n", get_time() - philo->data->start_time, \
philo->id);
		pthread_mutex_unlock(&philo->data->log_mutex);
		safe_sleep(philo->data->time_to_sleep);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!check_death(philo->data))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
