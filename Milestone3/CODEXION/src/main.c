/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:29:16 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:29:18 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_sim	sim;

	memset(&sim, 0, sizeof(t_sim));
	if (parsing(ac, av, &sim.config))
		return (1);
	if (init_sim(&sim))
		return (1);
	run_sim(&sim);
	cleanup_sim(&sim);
	return (0);
}
