/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:10:08 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:10:16 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// long	calculate_priority_key(t_simu *simu, t_coder *coder)
// {
// 	if (strcmp(simu->scheduler, "fifo") == 0)
// 		return (get_time_ms());
// 	else if (strcmp(simu->scheduler, "edf") == 0)
// 		return (coder->last_start_compile_ms + simu->time_to_burnout);
// 	return (0);
// }

long	calculate_priority_key(t_simu *simu, t_coder *coder)
{
	long	ticket;
	long	deadline;

	if (strcmp(simu->scheduler, "edf") == 0)
	{
		pthread_mutex_lock(&coder->mutex_state);
		deadline = coder->last_start_compile_ms + simu->time_to_burnout;
		pthread_mutex_unlock(&coder->mutex_state);
		return (deadline);
	}
	if (strcmp(simu->scheduler, "fifo") == 0)
	{
		pthread_mutex_lock(&simu->mutex_stop);
		simu->next_ticket++;
		ticket = simu->next_ticket;
		pthread_mutex_unlock(&simu->mutex_stop);
		return (ticket);
	}
	return (0);
}

static int	rotation_index(t_simu *simu, int id)
{
	if (id % 2 == 1)
		return ((id - 1) / 2);
	return ((simu->number_of_coders + 1) / 2 + id / 2 - 1);
}

long	start_delay(t_simu *simu, int id)
{
	long	period;

	period = simu->time_to_compile + simu->dongle_cooldown;
	return (rotation_index(simu, id) * period / (simu->number_of_coders / 2));
}

void	prejoin_queues(t_simu *simu)
{
	int		k;
	int		i;
	long	key;
	t_coder	*c;

	if (simu->number_of_coders % 2 == 0 || simu->number_of_coders == 1)
		return ;
	k = 0;
	while (k < simu->number_of_coders)
	{
		i = 0;
		while (rotation_index(simu, simu->coders[i].id) != k)
			i++;
		c = &simu->coders[i];
		key = ++simu->next_ticket;
		if (strcmp(simu->scheduler, "edf") == 0)
			key = c->last_start_compile_ms + simu->time_to_burnout
				- simu->number_of_coders + k;
		heap_push(&c->dongle_left->queue, key, c->id);
		heap_push(&c->dongle_right->queue, key, c->id);
		c->queued = true;
		k++;
	}
}
