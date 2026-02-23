/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:14:21 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/23 19:15:29 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks_odd(t_philo	*philo)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->first_fork]))
		return (0);
	print_status(philo, "has taken a fork");
	if (pthread_mutex_lock(&philo->data->forks[philo->second_fork]))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
		return (0);
	}
	else
		print_status(philo, "has taken a fork");
	return (1);
}

int	take_forks_even(t_philo	*philo)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->second_fork]))
		return (0);
	print_status(philo, "has taken a fork");
	if (pthread_mutex_lock(&philo->data->forks[philo->first_fork]))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
		return (0);
	}
	else
		print_status(philo, "has taken a fork");
	return (1);
}

int	take_forks(t_philo *philo)
{
	int	result;

	if (philo->id % 2 != 0)
		result = take_forks_odd(philo);
	else
		result = take_forks_even(philo);
	return (result);
}

int	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!take_forks(philo))
		return (0);
	if (!check_death(data))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time();
		philo->meals++;
		pthread_mutex_unlock(&philo->meal_mutex);
		print_status(philo, "is eating");
		safe_sleep(data->time_to_eat);
	}
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&data->forks[philo->second_fork]);
		pthread_mutex_unlock(&data->forks[philo->first_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->first_fork]);
		pthread_mutex_unlock(&data->forks[philo->second_fork]);
	}
	return (1);
}
