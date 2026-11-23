/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:10:08 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 10:12:46 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_queue_sync(t_sim *sim)
{
	if (pthread_mutex_init(&sim->queue_mutex, NULL))
		return (1);
	if (pthread_cond_init(&sim->queue_cond, NULL))
	{
		pthread_mutex_destroy(&sim->queue_mutex);
		return (1);
	}
	return (0);
}

static long	get_priority(t_coder *coder, t_dongle *dongle)
{
	long	priority;

	if (!coder->sim->params.edf_mode)
	{
		priority = dongle->next_ticket;
		dongle->next_ticket++;
		return (priority);
	}
	pthread_mutex_lock(&coder->sim->state_mutex);
	priority = coder->last_compile_start + coder->sim->params.time_to_burnout;
	pthread_mutex_unlock(&coder->sim->state_mutex);
	return (priority);
}

int	enqueue_request(t_coder *coder)
{
	long	priority;

	priority = get_priority(coder, coder->left_dongle);
	if (heap_push(&coder->left_dongle->waiters, priority, coder->id) != 0)
		return (1);
	priority = get_priority(coder, coder->right_dongle);
	if (heap_push(&coder->right_dongle->waiters, priority, coder->id) != 0)
		return (1);
	return (0);
}

long	ready_time(t_coder *coder)
{
	t_dongle	*left;
	t_dongle	*right;

	left = coder->left_dongle;
	right = coder->right_dongle;
	if (left->in_use || right->in_use)
		return (-1);
	if (heap_peek_id(&left->waiters) != coder->id && left->waiters.size > 0)
		return (-1);
	if (heap_peek_id(&right->waiters) != coder->id && right->waiters.size > 0)
		return (-1);
	if (left->available_at > right->available_at)
		return (left->available_at);
	return (right->available_at);
}
