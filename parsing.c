/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:12:09 by alicigar          #+#    #+#             */
/*   Updated: 2026/02/13 21:37:30 by alicigar         ###   ########.fr       */
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
