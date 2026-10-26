/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 10:00:00 by login             #+#    #+#             */
/*   Updated: 2026/10/26 10:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_state(t_coder *c, char *msg)
{
	t_sim	*sim;

	sim = c->sim;
	pthread_mutex_lock(&sim->print_mutex);
	if (!is_stopped(sim))
		printf("%ld %d %s\n", get_time_ms() - sim->start_time, c->id, msg);
	pthread_mutex_unlock(&sim->print_mutex);
}

void	log_burnout(t_sim *sim, int id)
{
	pthread_mutex_lock(&sim->print_mutex);
	set_stop(sim);
	printf("%ld %d burned out\n", get_time_ms() - sim->start_time, id);
	pthread_mutex_unlock(&sim->print_mutex);
}
