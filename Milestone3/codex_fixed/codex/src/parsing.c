/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:10:02 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:10:04 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	check_value(int arg, long value)
{
	if (value == 0 && arg != 4 && arg != 5)
	{
		if (arg == 1)
			printf("Number of coders must be greater than 0.\n");
		else if (arg == 2)
			printf("Time to burnout must be greater than 0.\n");
		else if (arg == 3)
			printf("Time to compile must be greater than 0.\n");
		else if (arg == 6)
			printf("Required compilations must be greater than 0.\n");
		else if (arg == 7)
			printf("Dongle cooldown must be greater than 0.\n");
		return (false);
	}
	if (arg == 1 && value > 400)
	{
		printf("Number of coders must be between 1 and 400.\n");
		return (false);
	}
	return (true);
}

bool	parse_number(int arg, char **argv, long *values)
{
	if (!is_valid_number(argv[arg]))
	{
		printf("Argument %d must be a positive integer.\n", arg);
		return (false);
	}
	values[arg - 1] = ft_atol(argv[arg]);
	if (values[arg - 1] == -1)
	{
		printf("Argument %d is too large.\n", arg);
		return (false);
	}
	return (check_value(arg, values[arg - 1]));
}

static bool	check_scheduler(char *scheduler)
{
	if (strcmp(scheduler, "fifo") == 0 || strcmp(scheduler, "edf") == 0)
		return (true);
	printf("Scheduler must be 'fifo' or 'edf'.\n");
	return (false);
}

bool	parse_args(int argc, char **argv, t_simu *simu)
{
	long	values[7];

	if (argc == 1)
		return (false);
	if (argc != 9)
	{
		printf("Error: expected 7 numeric arguments and a scheduler.\n");
		return (false);
	}
	if (!check_numbers(argv, values) || !check_scheduler(argv[8]))
		return (false);
	simu->number_of_coders = (int)values[0];
	simu->time_to_burnout = values[1];
	simu->time_to_compile = values[2];
	simu->time_to_debug = values[3];
	simu->time_to_refactor = values[4];
	simu->number_of_compiles_required = (int)values[5];
	simu->dongle_cooldown = values[6];
	cpy(simu->scheduler, argv[8]);
	return (true);
}
