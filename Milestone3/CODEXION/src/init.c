/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:29:01 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:29:03 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	assign_dongles(t_sim *sim, int i)
{
	int	n;
	int	left;
	int	right;

	n = sim->config.number_of_coders;
	left = (i + n - 1) % n;
	right = i;
	if (left < right)
	{
		sim->coders[i].first = &sim->dongles[left];
		sim->coders[i].second = &sim->dongles[right];
	}
	else
	{
		sim->coders[i].first = &sim->dongles[right];
		sim->coders[i].second = &sim->dongles[left];
	}
}

static int	init_coders(t_sim *sim)
{
	int	i;
	int	n;

	n = sim->config.number_of_coders;
	sim->coders = malloc(sizeof(t_coder) * n);
	if (!sim->coders)
		return (1);
	i = 0;
	while (i < n)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].compile_count = 0;
		sim->coders[i].last_compile_start = sim->start_time;
		sim->coders[i].sim = sim;
		assign_dongles(sim, i);
		i++;
	}
	return (0);
}

static int	init_mutexes(t_sim *sim)
{
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->state_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->print_mutex);
		return (1);
	}
	return (0);
}

int	init_sim(t_sim *sim)
{
	sim->stop = 0;
	sim->n_dongles = 0;
	sim->coders = NULL;
	sim->dongles = NULL;
	if (init_mutexes(sim))
		return (1);
	sim->start_time = get_time_ms();
	if (init_dongles(sim) || init_coders(sim))
	{
		cleanup_sim(sim);
		return (1);
	}
	return (0);
}
