/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:29:19 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/20 12:11:03 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	is_stopped(t_sim *sim)
{
	int	stopped;

	pthread_mutex_lock(&sim->state_mutex);
	stopped = sim->stop;
	pthread_mutex_unlock(&sim->state_mutex);
	return (stopped);
}

void	smart_sleep(long ms, t_sim *sim)
{
	long	end;

	end = get_time_ms() + ms;
	while (get_time_ms() < end)
	{
		if (is_stopped(sim))
			return ;
		usleep(500);
	}
}
