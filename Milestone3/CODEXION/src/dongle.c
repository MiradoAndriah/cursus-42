/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:28:34 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:28:36 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long	make_key(t_coder *c, t_dongle *d)
{
	long	deadline;

	if (c->sim->config.scheduler == FIFO)
	{
		d->seq++;
		return (d->seq);
	}
	pthread_mutex_lock(&c->sim->state_mutex);
	deadline = c->last_compile_start + c->sim->config.time_to_burnout;
	pthread_mutex_unlock(&c->sim->state_mutex);
	return (deadline);
}

static int	can_take(t_coder *c, t_dongle *d)
{
	if (d->queue.size == 0 || d->queue.data[0].coder_id != c->id)
		return (0);
	if (d->is_taken)
		return (0);
	return (get_time_ms() >= d->available_at);
}

static void	wait_dongle(t_coder *c, t_dongle *d)
{
	struct timespec	ts;

	if (d->queue.data[0].coder_id == c->id && !d->is_taken)
	{
		set_abs_time(&ts, d->available_at);
		pthread_cond_timedwait(&d->cond, &d->mutex, &ts);
	}
	else
		pthread_cond_wait(&d->cond, &d->mutex);
}

int	take_dongle(t_coder *c, t_dongle *d)
{
	t_request	req;

	pthread_mutex_lock(&d->mutex);
	req.coder_id = c->id;
	req.key = make_key(c, d);
	if (heap_push(&d->queue, req))
	{
		pthread_mutex_unlock(&d->mutex);
		return (1);
	}
	while (!is_stopped(c->sim) && !can_take(c, d))
		wait_dongle(c, d);
	if (is_stopped(c->sim))
	{
		pthread_mutex_unlock(&d->mutex);
		return (1);
	}
	heap_pop(&d->queue);
	d->is_taken = 1;
	pthread_mutex_unlock(&d->mutex);
	log_state(c, "has taken a dongle");
	return (0);
}

void	release_dongle(t_coder *c, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->is_taken = 0;
	d->available_at = get_time_ms() + c->sim->config.dongle_cooldown;
	pthread_cond_broadcast(&d->cond);
	pthread_mutex_unlock(&d->mutex);
}
