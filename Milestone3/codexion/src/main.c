/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:52 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 10:09:57 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_sim		sim;
	int			exit_code;

	if (argc == 1)
		return (1);
	if (parse_args(argc, argv, &params) != 0)
		return (1);
	if (init_sim(&sim, &params))
		return (1);
	exit_code = run_simulation(&sim);
	cleanup_sim(&sim);
	return (exit_code);
}
