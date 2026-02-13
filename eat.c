/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 23:36:08 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/13 22:06:38 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_even(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	if (!check_death(data))
	{
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d has taken a fork\n", get_time() - \
data->start_time, philo->id);
		pthread_mutex_unlock(&data->log_mutex);
	}
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	if (!check_death(data))
	{
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d has taken a fork\n", get_time() - \
data->start_time, philo->id);
		pthread_mutex_unlock(&data->log_mutex);
	}
}

void	take_forks_odd(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	if (!check_death(data))
	{
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d has taken a fork\n", get_time() - \
data->start_time, philo->id);
		pthread_mutex_unlock(&data->log_mutex);
	}
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	if (!check_death(data))
	{
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d has taken a fork\n", get_time() - \
data->start_time, philo->id);
		pthread_mutex_unlock(&data->log_mutex);
	}
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
		take_forks_even(philo);
	else
		take_forks_odd(philo);
	if (!check_death(data))
	{
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d is eating\n", get_time() - data->start_time, philo->id);
		philo->last_meal = get_time();
		philo->meals++;
		pthread_mutex_unlock(&data->log_mutex);
		safe_sleep(data->time_to_eat);
	}
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}
