/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:29:08 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:29:10 by herinaan         ###   ########.fr       */
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
