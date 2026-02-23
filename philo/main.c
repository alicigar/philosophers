/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:25:47 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/23 19:04:59 by alicigar         ###   ########.fr       */
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
	if (initialize_all(&data, argc, argv))
		return (1);
	if (data.number_of_philosophers == 1)
	{
		data.start_time = get_time();
		printf("%ld 1 has taken a fork\n", get_time() - data.start_time);
		safe_sleep(data.time_to_die);
		printf("%ld 1 died\n", get_time() - data.start_time);
		cleanup(&data);
		return (0);
	}
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
