/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:45 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:09:47 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_action(t_simu *simu, int coder_id, char *message)
{
	pthread_mutex_lock(&simu->mutex_log);
	if (!simulation_is_complete(simu))
		printf("%ld %d %s\n", get_time_ms() - simu->start_time_ms, coder_id,
			message);
	pthread_mutex_unlock(&simu->mutex_log);
}

void	log_burnout(t_simu *simu, int coder_id)
{
	pthread_mutex_lock(&simu->mutex_log);
	pthread_mutex_lock(&simu->mutex_stop);
	if (!simu->simulation_complete)
	{
		simu->simulation_complete = true;
		printf("%ld %d burned out\n", get_time_ms() - simu->start_time_ms,
			coder_id);
	}
	pthread_mutex_unlock(&simu->mutex_stop);
	pthread_mutex_unlock(&simu->mutex_log);
	check_in(simu);
}

void	check_in(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->nb_dongles)
	{
		pthread_mutex_lock(&simu->dongles[i].mutex);
		pthread_cond_broadcast(&simu->dongles[i].cond);
		pthread_mutex_unlock(&simu->dongles[i].mutex);
		i++;
	}
}
