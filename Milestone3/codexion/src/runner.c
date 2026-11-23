/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 10:13:22 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 13:27:02 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_start_time(t_sim *sim)
{
	int	i;

	sim->start_time = get_time_ms();
	i = 0;
	while (i < sim->params.coder_count)
	{
		sim->coders[i].last_compile_start = sim->start_time;
		sim->coders[i].next_start = sim->start_time
			+ sim->coders[i].start_offset;
		i++;
	}
}

static int	spawn_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->params.coder_count)
	{
		if (pthread_create(&sim->coders[i].thread, NULL, coder_routine,
				&sim->coders[i]))
			return (i);
		i++;
	}
	return (i);
}

static void	join_coders(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}

int	run_simulation(t_sim *sim)
{
	int	created;
	int	monitor_ok;

	init_start_time(sim);
	created = spawn_coders(sim);
	monitor_ok = 0;
	if (created == sim->params.coder_count)
		monitor_ok = !pthread_create(&sim->monitor_thread, NULL,
				monitor_routine, sim);
	if (!monitor_ok)
		request_stop(sim);
	join_coders(sim, created);
	if (monitor_ok)
		pthread_join(sim->monitor_thread, NULL);
	return (created != sim->params.coder_count || !monitor_ok);
}
