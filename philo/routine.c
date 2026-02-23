/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:03:48 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/23 19:15:41 by alicigar         ###   ########.fr       */
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

void	*philo_routine(void	*arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 != 0)
		safe_sleep(data->time_to_eat);
	while (!check_death(philo->data))
	{
		if (philo_eat(philo))
		{
			if (!check_death(philo->data))
			{
				print_status(philo, "is sleeping");
				safe_sleep(philo->data->time_to_sleep);
			}
			if (!check_death(philo->data))
			{
				print_status(philo, "is thinking");
				if (data->number_of_philosophers % 2 != 0)
					safe_sleep(1);
			}
		}
	}
	return (NULL);
}
