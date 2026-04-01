/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:56:58 by brportos          #+#    #+#             */
/*   Updated: 2026/03/31 10:30:50 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	check_min_max(const char *nptr, int sign, int *is_error)
{
	long	nbr;

	nbr = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - '0');
		if (nbr * sign < INT_MIN || nbr * sign > INT_MAX)
		{
			write(2, "Error\n", 6);
			*is_error = 1;
			return (0);
		}
		nptr++;
	}
	return (sign * nbr);
}

int	ft_atoi(const char *nptr, int *is_error)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		{
			sign *= -1;
			i++;
		}
		else
			i++;
	}
	return ((int)check_min_max(nptr + i, sign, is_error));
}
