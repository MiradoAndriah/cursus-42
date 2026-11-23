/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teardown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:09 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 10:05:14 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_dongles(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		heap_destroy(&sim->dongles[i].waiters);
		i++;
	}
}

void	destroy_queue_sync(t_sim *sim)
{
	pthread_mutex_destroy(&sim->queue_mutex);
	pthread_cond_destroy(&sim->queue_cond);
}

void	destroy_mutexes(t_sim *sim)
{
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->state_mutex);
}

void	cleanup_sim(t_sim *sim)
{
	if (sim->dongles)
	{
		destroy_dongles(sim, sim->params.coder_count);
		free(sim->dongles);
	}
	free(sim->coders);
	destroy_queue_sync(sim);
	destroy_mutexes(sim);
}
