/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:12:09 by alicigar          #+#    #+#             */
/*   Updated: 2026/01/26 18:57:43 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_arg(const char *str)
{
	long long	num;

	if (!str || !*str)
		return (0);
	num = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		num = num * 10 + (*str - '0');
		if (num > 2147483647)
			return (0);
		str++;
	}
	return (1);
}

int	input_checker(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	if (argc < 5 || argc > 6)
		return (1);
	while (i < argc)
	{
		if (!is_valid_arg(argv[i]))
			return (1);
		num = ft_atoi(argv[i]);
		if (argc == 6 && i == 5)
		{
			if (num < 0)
				return (1);
		}
		else
		{
			if (num <= 0)
				return (1);
		}
		i++;
	}
	return (0);
}

//que cada argumento es un numero valido
//que no haya numeros negativos
//que time_to_die, time_to_eat, time_to_sleep no sean 0
//y must_eat SI puede ser 0
//que no haya overflow
//si pones 0 filosofos, no hay simulacion