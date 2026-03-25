/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:56:58 by brportos          #+#    #+#             */
/*   Updated: 2026/03/21 08:19:14 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	Check_min_max(const char *nptr, int sign)
{
	long	nbr;

	nbr = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - '0');
		if (nbr * sign < INT_MIN || nbr * sign > INT_MAX)
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		nptr++;
	}
	return (sign * nbr);
}

int	ft_atoi(const char *nptr)
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
	return ((int)Check_min_max(nptr + i, sign));
}
