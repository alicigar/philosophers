/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:03:48 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/02 20:34:58 by alicigar         ###   ########.fr       */
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

void	philo_eat(t_philo *philo)
{
	t_data	*data = philo->data;

    if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		if (!check_death(data))
		{
			pthread_mutex_lock(&data->log_mutex);
			printf("%ld %d has taken a fork\n", \
get_time() - data->start_time, philo->id);
			pthread_mutex_unlock(&data->log_mutex);
		}
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		if (!check_death(data))
		{
			pthread_mutex_lock(&data->log_mutex);
			printf("%ld %d has taken a fork\n", \
get_time() - data->start_time, philo->id);
			pthread_mutex_unlock(&data->log_mutex);
		}
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		if (!check_death(data))
		{
			pthread_mutex_lock(&data->log_mutex);
			printf("%ld %d has taken a fork\n", \
get_time() - data->start_time, philo->id);
			pthread_mutex_unlock(&data->log_mutex);
		}
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		if (!check_death(data))
		{
			pthread_mutex_lock(&data->log_mutex);
			printf("%ld %d has taken a fork\n", \
get_time() - data->start_time, philo->id);
			pthread_mutex_unlock(&data->log_mutex);
		}
	}
	if (!check_death(data))
	{
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d is eating\n", \
get_time() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->log_mutex);
		philo->last_meal = get_time();
		philo->meals++;
		safe_sleep(data->time_to_eat);
	}
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
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
		usleep(1000);
	while (!check_death(philo->data))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
