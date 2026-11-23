/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 10:13:25 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 10:14:09 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_stopped(t_sim *sim)
{
	int	stopped;

	pthread_mutex_lock(&sim->state_mutex);
	stopped = sim->stop_flag;
	pthread_mutex_unlock(&sim->state_mutex);
	return (stopped);
}

void	wake_waiters(t_sim *sim)
{
	pthread_mutex_lock(&sim->queue_mutex);
	pthread_cond_broadcast(&sim->queue_cond);
	pthread_mutex_unlock(&sim->queue_mutex);
}

void	request_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->stop_flag = 1;
	pthread_mutex_unlock(&sim->state_mutex);
	wake_waiters(sim);
}
