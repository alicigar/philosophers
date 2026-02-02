/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:25:47 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/02 22:24:08 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

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
	if (data.number_of_philosophers == 1)
	{
		printf("0 1 has taken a fork\n");
		safe_sleep(data.time_to_die);
		printf("%d 1 died\n", data.time_to_die);
		cleanup(&data);
		return (0);
	}
	start_simulation(&data);
	cleanup(&data);
	/*printf("argv[1] = %s\n", argv[1]);
	printf("argv[2] = %s\n", argv[2]);
	printf("argv[3] = %s\n", argv[3]);
	printf("argv[4] = %s\n", argv[4]);
	if (argc == 6) 
		printf("argv[5] = %s\n", argv[5]);*/
	return (0);
}
