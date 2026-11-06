/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:08:59 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:09:02 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	check_numbers(char **argv, long *values)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (!parse_number(i, argv, values))
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

long	ft_atol(const char *str)
{
	long	result;
	int		i;
	int		digit;

	result = 0;
	i = (str[0] == '+');
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (-1);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

char	*cpy(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
