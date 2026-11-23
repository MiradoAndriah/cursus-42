/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:45 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 13:26:48 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_event(t_coder *coder, char *msg)
{
	t_sim	*sim;
	int		stopped;

	sim = coder->sim;
	pthread_mutex_lock(&sim->print_mutex);
	pthread_mutex_lock(&sim->state_mutex);
	stopped = sim->stop_flag;
	pthread_mutex_unlock(&sim->state_mutex);
	if (!stopped)
		printf("%ld %d %s\n", get_time_ms() - sim->start_time, coder->id, msg);
	pthread_mutex_unlock(&sim->print_mutex);
}

void	log_burnout(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&sim->print_mutex);
	if (!is_stopped(sim))
		printf("%ld %d burned out\n", get_time_ms() - sim->start_time,
			coder->id);
	request_stop(sim);
	pthread_mutex_unlock(&sim->print_mutex);
}
