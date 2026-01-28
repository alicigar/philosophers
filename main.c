/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:25:47 by alicigar          #+#    #+#             */
/*   Updated: 2026/01/28 20:37:10 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (input_checker(argc, argv))
	{
		printf("Error: wrong input\n");
		return (1);
	}
	if (init_data(&data, argc, argv))
		return (1);
	if (init_forks(&data))
	{
		cleanup(&data);
		return (1);
	}
	if (init_philos(&data))
	{
		cleanup(&data);
		return (1);
	}
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_create(&data.philos[i].thread, NULL, \
philo_routine, &data.philos[i]);
		i++;
	}
	printf("Philos: %d\n", data.number_of_philosophers);
	printf("Die: %dms | Eat: %dms | Sleep: %dms\n", \
data.time_to_die, data.time_to_eat, data.time_to_sleep);
	if (data.must_eat != -1)
		printf("Must eat: %d times\n", data.must_eat);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		printf("Philo %d: left=%d right=%d\n", data.philos[i].id, \
data.philos[i].left_fork, data.philos[i].right_fork);
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	cleanup(&data);
	/*printf("argv[1] = %s\n", argv[1]);
	printf("argv[2] = %s\n", argv[2]);
	printf("argv[3] = %s\n", argv[3]);
	printf("argv[4] = %s\n", argv[4]);
	if (argc == 6) 
		printf("argv[5] = %s\n", argv[5]);*/
	return (0);
}
