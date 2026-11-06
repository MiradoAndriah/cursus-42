/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:15 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/04 09:20:39 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	*single_coder(t_coder *coder)
{
	log_action(coder->simu, coder->id, "has taken a dongle");
	while (!simulation_is_complete(coder->simu))
		usleep(1000);
	return (NULL);
}

static int	wait_for_completion(t_simu *simu, long duration_ms)
{
	long	start;

	start = get_time_ms();
	while (!simulation_is_complete(simu) && get_time_ms() - start < duration_ms)
		usleep(200);
	return (!simulation_is_complete(simu));
}

static int	compile_phase(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex_state);
	coder->last_start_compile_ms = get_time_ms();
	pthread_mutex_unlock(&coder->mutex_state);
	log_action(coder->simu, coder->id, "is compiling");
	if (!wait_for_completion(coder->simu, coder->simu->time_to_compile))
	{
		release_dongle(coder->dongle_left);
		release_dongle(coder->dongle_right);
		return (0);
	}
	release_dongle(coder->dongle_left);
	release_dongle(coder->dongle_right);
	pthread_mutex_lock(&coder->mutex_state);
	coder->nb_compiles++;
	pthread_mutex_unlock(&coder->mutex_state);
	if (all_compiled(coder->simu))
	{
		stop_simulation(coder->simu);
		return (0);
	}
	return (1);
}

static void	verification(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!simulation_is_complete(coder->simu))
	{
		if (!request_dongles(coder, calculate_priority_key(coder->simu, coder)))
			break ;
		log_action(coder->simu, coder->id, "has taken a dongle");
		log_action(coder->simu, coder->id, "has taken a dongle");
		if (!compile_phase(coder))
			break ;
		if (simulation_is_complete(coder->simu))
			break ;
		log_action(coder->simu, coder->id, "is debugging");
		if (!wait_for_completion(coder->simu, coder->simu->time_to_debug))
			break ;
		log_action(coder->simu, coder->id, "is refactoring");
		if (!wait_for_completion(coder->simu, coder->simu->time_to_refactor))
			break ;
	}
}

void	*routine_coder(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->simu->number_of_coders == 1)
		return (single_coder(coder));
	if (coder->simu->number_of_coders % 2 == 0)
	{
		if (coder->id % 2 == 0 && !wait_for_completion(coder->simu,
				coder->simu->time_to_compile))
			return (NULL);
	}
	else if (!wait_for_completion(coder->simu, start_delay(coder->simu,
				coder->id)))
		return (NULL);
	verification(coder);
	return (NULL);
}
