/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:10:02 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 14:37:03 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	set_policy(char *s, t_params *params)
{
	if (strcmp(s, "fifo") == 0)
		params->edf_mode = 0;
	else if (strcmp(s, "edf") == 0)
		params->edf_mode = 1;
	else
		return (1);
	return (0);
}

static void	fill_params(long *values, t_params *params)
{
	params->coder_count = (int)values[0];
	params->time_to_burnout = values[1];
	params->time_to_compile = values[2];
	params->time_to_debug = values[3];
	params->time_to_refactor = values[4];
	params->compile_goal = (int)values[5];
	params->dongle_cooldown = values[6];
}

int	parse_args(int argc, char **argv, t_params *params)
{
	long	values[7];

	if (argc != 9)
	{
		fprintf(stderr, "Usage: %s coders burnout compile debug refactor "
			"compiles_required cooldown fifo|edf\n", argv[0]);
		return (1);
	}
	if (read_values(argv, values) || check_values(values))
		return (1);
	if (set_policy(argv[8], params))
		return (print_error("scheduler must be 'fifo' or 'edf'\n"));
	fill_params(values, params);
	return (0);
}
