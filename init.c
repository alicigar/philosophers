/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:42:37 by alicigar          #+#    #+#             */
/*   Updated: 2026/01/27 19:12:51 by alicigar         ###   ########.fr       */
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
	pthtread_mutex_init(&data->death_mutex, NULL);
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
		i++;
	}
	return (0);
}

/*
typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	t_philo			*philos;
	long			start_time;
	int				dead;
}	t_data;
*/

/*
pthread_mutex_t mi_candado;  (Declarar el candado)
pthread_mutex_init(&mi_candado, NULL); (Crearlo/inicializarlo)

pthread_mutex_lock(&mi_candado); (Cerrar el candado)

código ya protegido
pthread_mutex_unlock(&mi_candado); (Abrir el candado)
pthread_mutex_destroy(&mi_candado); (Destruirlo al final)
*/