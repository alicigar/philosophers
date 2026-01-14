/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:42:51 by alicigar          #+#    #+#             */
/*   Updated: 2026/01/14 22:39:38 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int n)

{
	if (n >= 48 && n <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	number;
	int	neg;

	number = 0;
	neg = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr ++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = number * 10 + (*nptr - '0');
		nptr++;
	}
	return (neg * number);
}
