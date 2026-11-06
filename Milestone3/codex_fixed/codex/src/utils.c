/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:10:34 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:10:36 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	time_elapsed_since(long t)
{
	return (get_time_ms() - t);
}

bool	simulation_is_complete(t_simu *simu)
{
	bool	result;

	pthread_mutex_lock(&simu->mutex_stop);
	result = simu->simulation_complete;
	pthread_mutex_unlock(&simu->mutex_stop);
	return (result);
}

void	stop_simulation(t_simu *simu)
{
	int	i;

	pthread_mutex_lock(&simu->mutex_stop);
	simu->simulation_complete = true;
	pthread_mutex_unlock(&simu->mutex_stop);
	i = 0;
	while (i < simu->nb_dongles)
	{
		pthread_mutex_lock(&simu->dongles[i].mutex);
		pthread_cond_broadcast(&simu->dongles[i].cond);
		pthread_mutex_unlock(&simu->dongles[i].mutex);
		i++;
	}
}

bool	heap_is_empty(t_heap *heap)
{
	return (heap->size == 0);
}
