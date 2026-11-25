/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 10:12:53 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/24 15:03:25 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_one_dongle(t_dongle *dongle)
{
	dongle->in_use = 0;
	dongle->available_at = 0;
	dongle->next_ticket = 0;
	return (heap_init(&dongle->waiters, 2));
}

static int	init_dongles(t_sim *sim)
{
	int	i;
	int	n;

	n = sim->params.coder_count;
	sim->dongles = malloc(sizeof(t_dongle) * n);
	if (!sim->dongles)
		return (print_error("could not allocate, number of coder too large"));
	i = 0;
	while (i < n)
	{
		if (init_one_dongle(&sim->dongles[i]))
		{
			destroy_dongles(sim, i);
			free(sim->dongles);
			sim->dongles = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_coders(t_sim *sim)
{
	int	i;
	int	n;

	n = sim->params.coder_count;
	sim->coders = malloc(sizeof(t_coder) * n);
	if (!sim->coders)
		return (1);
	i = 0;
	while (i < n)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].left_dongle = &sim->dongles[(i + n - 1) % n];
		sim->coders[i].right_dongle = &sim->dongles[i];
		sim->coders[i].last_compile_start = sim->start_time;
		sim->coders[i].compile_count = 0;
		sim->coders[i].start_offset = compute_offset(&sim->params, sim->cycle, i
				+ 1);
		sim->coders[i].next_start = 0;
		sim->coders[i].sim = sim;
		i++;
	}
	return (0);
}

static int	init_mutexes(t_sim *sim)
{
	if (pthread_mutex_init(&sim->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&sim->state_mutex, NULL))
	{
		pthread_mutex_destroy(&sim->print_mutex);
		return (1);
	}
	return (0);
}

int	init_sim(t_sim *sim, t_params *params)
{
	memset(sim, 0, sizeof(t_sim));
	sim->params = *params;
	sim->cycle = compute_cycle(&sim->params);
	if (init_mutexes(sim))
		return (1);
	if (init_queue_sync(sim))
	{
		destroy_mutexes(sim);
		return (1);
	}
	if (init_dongles(sim) || init_coders(sim))
	{
		cleanup_sim(sim);
		return (1);
	}
	return (0);
}
