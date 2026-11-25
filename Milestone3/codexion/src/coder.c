/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:15 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 13:26:38 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	wait_stop(t_coder *coder)
{
	while (!is_stopped(coder->sim))
		usleep(500);
	return (1);
}

static int	acquire_or_stop(t_coder *coder)
{
	if (coder->left_dongle == coder->right_dongle)
	{
		log_event(coder, "has taken a dongle");
		return (wait_stop(coder));
	}
	return (acquire_both_dongles(coder));
}

static void	start_compile(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&sim->state_mutex);
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&sim->state_mutex);
	coder->next_start = coder->last_compile_start + sim->cycle;
	log_event(coder, "is compiling");
}

static void	finish_compile(t_coder *coder)
{
	release_both_dongles(coder, coder->sim->params.dongle_cooldown);
	pthread_mutex_lock(&coder->sim->state_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->sim->state_mutex);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_sim	*sim;

	coder = (t_coder *)arg;
	sim = coder->sim;
	while (!is_stopped(sim))
	{
		wait_for_slot(coder);
		if (acquire_or_stop(coder))
			return (NULL);
		start_compile(coder);
		sleep_ms(sim, sim->params.time_to_compile);
		finish_compile(coder);
		if (coder->compile_count >= sim->params.compile_goal)
			break ;
		log_event(coder, "is debugging");
		sleep_ms(sim, sim->params.time_to_debug);
		log_event(coder, "is refactoring");
		sleep_ms(sim, sim->params.time_to_refactor);
	}
	return (NULL);
}
