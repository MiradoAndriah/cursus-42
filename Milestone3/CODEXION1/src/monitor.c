/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 10:00:00 by login             #+#    #+#             */
/*   Updated: 2026/10/26 10:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	find_burnout(t_sim *sim)
{
	int		i;
	int		id;
	long	now;

	id = 0;
	i = 0;
	now = get_time_ms();
	pthread_mutex_lock(&sim->state_mutex);
	while (i < sim->config.number_of_coders && id == 0)
	{
		if (now - sim->coders[i].last_compile_start
			> sim->config.time_to_burnout)
			id = sim->coders[i].id;
		i++;
	}
	pthread_mutex_unlock(&sim->state_mutex);
	return (id);
}

static int	all_done(t_sim *sim)
{
	int	i;
	int	done;

	done = 1;
	i = 0;
	pthread_mutex_lock(&sim->state_mutex);
	while (i < sim->config.number_of_coders)
	{
		if (sim->coders[i].compile_count
			< sim->config.number_of_compiles_required)
			done = 0;
		i++;
	}
	pthread_mutex_unlock(&sim->state_mutex);
	return (done);
}

void	wake_all(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n_dongles)
	{
		pthread_mutex_lock(&sim->dongles[i].mutex);
		pthread_cond_broadcast(&sim->dongles[i].cond);
		pthread_mutex_unlock(&sim->dongles[i].mutex);
		i++;
	}
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		id;

	sim = (t_sim *)arg;
	while (1)
	{
		id = find_burnout(sim);
		if (id != 0)
			log_burnout(sim, id);
		else if (all_done(sim))
			set_stop(sim);
		if (is_stopped(sim))
			break ;
		usleep(500);
	}
	wake_all(sim);
	return (NULL);
}
