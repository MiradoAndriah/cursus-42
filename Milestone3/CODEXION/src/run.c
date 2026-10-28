/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:29:42 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:29:44 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	start_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, &sim->coders[i]) != 0)
			return (i);
		i++;
	}
	return (i);
}

static void	join_all(t_sim *sim, int created, int monitor_ok)
{
	int	i;

	i = 0;
	while (i < created)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
	if (monitor_ok)
		pthread_join(sim->monitor, NULL);
}

void	run_sim(t_sim *sim)
{
	int	created;
	int	monitor_ok;

	monitor_ok = 0;
	created = start_coders(sim);
	if (created == sim->config.number_of_coders)
		monitor_ok = (pthread_create(&sim->monitor, NULL,
					monitor_routine, sim) == 0);
	if (!monitor_ok)
	{
		fprintf(stderr, "Error\n");
		set_stop(sim);
		wake_all(sim);
	}
	join_all(sim, created, monitor_ok);
}
