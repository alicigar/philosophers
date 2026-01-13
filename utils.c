/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicigar < alicigar@student.42malaga.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:42:51 by alicigar          #+#    #+#             */
/*   Updated: 2026/01/13 21:54:43 by alicigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)

{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	is_valid_arg(const char *str)
{
	long long	num;

	if (!str || !str)
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
	if (num == 0)
		return (0);
	return (1);
}

//input_checker
//que cada argumento es un numero valido
//que no haya numeros negativos
//que time_to_die, time_to_eat, time_to_sleep no sean 0
//y must_eat SI puede ser 0
//que no haya overflow
//si pones 0 filosofos, no hay simulacion