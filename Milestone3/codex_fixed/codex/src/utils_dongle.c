/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dongle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:10:29 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:10:31 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	can_take(t_dongle *d, int id, t_simu *simu)
{
	t_heap_node	*next;

	next = heap_peek(&d->queue);
	return (d->is_free && next && next->coder_id == id && (d->never_used
			|| get_time_ms() - d->last_release_ms >= simu->dongle_cooldown));
}

bool	try_take(t_dongle *a, t_dongle *b, int id, t_simu *simu)
{
	bool	ok;

	pthread_mutex_lock(&a->mutex);
	pthread_mutex_lock(&b->mutex);
	ok = can_take(a, id, simu) && can_take(b, id, simu);
	if (ok)
	{
		heap_pop(&a->queue);
		heap_pop(&b->queue);
		a->is_free = false;
		b->is_free = false;
		a->never_used = false;
		b->never_used = false;
	}
	pthread_mutex_unlock(&b->mutex);
	pthread_mutex_unlock(&a->mutex);
	return (ok);
}
