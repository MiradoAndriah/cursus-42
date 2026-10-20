/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:21:58 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/19 15:22:41 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long	parse_number(char *str)
{
	long	result;
	int		i;

	if (str[0] == '\0')
		return (-1);
	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result);
}

static int	check_numbers(char **av)
{
	long	n;
	int		i;

	i = 1;
	while (i <= 7)
	{
		n = parse_number(av[i]);
		if (n < 0 || (i != 7 && n < 1))
			return (1);
		i++;
	}
	return (0);
}

static void	fill_config(char **av, t_config *conf)
{
	conf->number_of_coders = parse_number(av[1]);
	conf->time_to_burnout = parse_number(av[2]);
	conf->time_to_compile = parse_number(av[3]);
	conf->time_to_debug = parse_number(av[4]);
	conf->time_to_refactor = parse_number(av[5]);
	conf->number_of_compiles_required = parse_number(av[6]);
	conf->dongle_cooldown = parse_number(av[7]);
	if (strcmp(av[8], "fifo") == 0)
		conf->scheduler = FIFO;
	else
		conf->scheduler = EDF;
}

int	parsing(int ac, char **av, t_config *conf)
{
	if (ac != 9 || check_numbers(av) || (strcmp(av[8], "fifo") != 0
			&& strcmp(av[8], "edf") != 0))
	{
		fprintf(stderr, "Error\n");
		return (1);
	}
	fill_config(av, conf);
	return (0);
}
