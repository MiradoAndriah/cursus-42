/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:21:11 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/20 12:08:19 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_config	config;

	if (parsing(ac, av, &config) != 0)
		return (1);
	i = 0;
	while (i < sim.config.number_of_coders)
	{
		printf("coder %d : first=%ld second=%ld\n", sim.coders[i].id,
			sim.coders[i].first - sim.dongles,
			sim.coders[i].second - sim.dongles);
		i++;
	}
	cleanup_sim(&sim);
	return (0);
}
