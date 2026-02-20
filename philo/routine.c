/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:03:48 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/20 20:24:28 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data	*data)
{
	int	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->log_mutex);
	if (!check_death(philo->data))
		printf("%ld %d %s\n", get_time() - \
philo->data->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->log_mutex);
}

void	take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->first_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&data->forks[philo->second_fork]);
	print_status(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	take_forks(philo);
	if (!check_death(data))
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time();
		philo->meals++;
		pthread_mutex_unlock(&philo->meal_mutex);
		print_status(philo, "is eating");
		safe_sleep(data->time_to_eat);
	}
	pthread_mutex_unlock(&data->forks[philo->second_fork]);
	pthread_mutex_unlock(&data->forks[philo->first_fork]);
}

void	*philo_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!check_death(philo->data))
	{
		philo_eat(philo);
		if (!check_death(philo->data))
		{
			print_status(philo, "is sleeping");
			safe_sleep(philo->data->time_to_sleep);
		}
		if (!check_death(philo->data))
			print_status(philo, "is thinking");
	}
	return (NULL);
}
