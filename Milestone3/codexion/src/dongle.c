/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:30 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 13:29:20 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	wait_until(t_sim *sim, long when)
{
	struct timespec	ts;

	ts.tv_sec = when / 1000;
	ts.tv_nsec = (when % 1000) * 1000000;
	pthread_cond_timedwait(&sim->queue_cond, &sim->queue_mutex, &ts);
}

static void	wait_turn(t_coder *coder)
{
	t_sim	*sim;
	long	when;

	sim = coder->sim;
	while (!is_stopped(sim))
	{
		when = ready_time(coder);
		if (when < 0)
			pthread_cond_wait(&sim->queue_cond, &sim->queue_mutex);
		else if (when > get_time_ms())
			wait_until(sim, when);
		else
			return ;
	}
}

int	acquire_both_dongles(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&sim->queue_mutex);
	if (enqueue_request(coder))
	{
		pthread_mutex_unlock(&sim->queue_mutex);
		return (1);
	}
	wait_turn(coder);
	if (is_stopped(sim))
	{
		pthread_mutex_unlock(&sim->queue_mutex);
		return (1);
	}
	heap_remove(&coder->left_dongle->waiters, coder->id);
	heap_remove(&coder->right_dongle->waiters, coder->id);
	coder->left_dongle->in_use = 1;
	coder->right_dongle->in_use = 1;
	pthread_cond_broadcast(&sim->queue_cond);
	pthread_mutex_unlock(&sim->queue_mutex);
	log_event(coder, "has taken a dongle");
	log_event(coder, "has taken a dongle");
	return (0);
}

void	release_both_dongles(t_coder *coder, long cooldown)
{
	t_sim	*sim;
	long	free_at;

	sim = coder->sim;
	free_at = get_time_ms() + cooldown;
	pthread_mutex_lock(&sim->queue_mutex);
	coder->left_dongle->in_use = 0;
	coder->left_dongle->available_at = free_at;
	coder->right_dongle->in_use = 0;
	coder->right_dongle->available_at = free_at;
	pthread_cond_broadcast(&sim->queue_cond);
	pthread_mutex_unlock(&sim->queue_mutex);
}
