/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 13:00:17 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 13:31:05 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_valid_number(char *s)
{
	long	n;
	int		i;

	i = 0;
	if (!s || s[0] == '\0')
		return (0);
	if (s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (0);
	n = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		n = n * 10 + (s[i] - '0');
		if (n > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	print_error(char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	return (1);
}

int	read_values(char **argv, long *values)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!is_valid_number(argv[i + 1]))
			return (print_error("negative values, "
					"letters and empty strings are not accepted"));
		values[i] = atoi(argv[i + 1]);
		i++;
	}
	return (0);
}

int	check_values(long *values)
{
	if (values[0] < 1)
		return (print_error("number of coders must be greater than 0"));
	if (values[2] < 1)
		return (print_error("time_to_compile must be greater than 0"));
	if (values[5] < 1)
		return (print_error("number of compiles must be greater than 0"));
	return (0);
}
