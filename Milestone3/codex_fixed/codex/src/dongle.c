/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:30 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/04 09:23:52 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	join_queue(t_dongle *d, int id, long key)
{
	pthread_mutex_lock(&d->mutex);
	heap_push(&d->queue, key, id);
	pthread_mutex_unlock(&d->mutex);
}

int	request_dongles(t_coder *c, long key)
{
	t_dongle	*a;
	t_dongle	*b;

	a = c->dongle_left;
	b = c->dongle_right;
	if (a->id > b->id)
	{
		a = c->dongle_right;
		b = c->dongle_left;
	}
	if (!c->queued)
	{
		join_queue(a, c->id, key);
		join_queue(b, c->id, key);
	}
	c->queued = false;
	while (!simulation_is_complete(c->simu))
	{
		if (try_take(a, b, c->id, c->simu))
			return (1);
		usleep(200);
	}
	return (0);
}

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_free = true;
	dongle->last_release_ms = get_time_ms();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
