/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:57 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 10:10:31 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_burnout(t_sim *sim)
{
	int		i;
	long	now;
	int		burned_id;

	i = 0;
	burned_id = 0;
	now = get_time_ms();
	pthread_mutex_lock(&sim->state_mutex);
	while (i < sim->params.coder_count && !burned_id)
	{
		if ((sim->coders[i].compile_count < sim->params.compile_goal)
			&& (now - sim->coders[i].last_compile_start
				>= sim->params.time_to_burnout))
			burned_id = sim->coders[i].id;
		i++;
	}
	pthread_mutex_unlock(&sim->state_mutex);
	return (burned_id);
}

static int	all_goals_met(t_sim *sim)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	pthread_mutex_lock(&sim->state_mutex);
	while (i < sim->params.coder_count)
	{
		if (sim->coders[i].compile_count < sim->params.compile_goal)
			done = 0;
		i++;
	}
	pthread_mutex_unlock(&sim->state_mutex);
	return (done);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		burned_id;

	sim = (t_sim *)arg;
	while (!is_stopped(sim))
	{
		burned_id = check_burnout(sim);
		if (burned_id != 0)
		{
			log_burnout(&sim->coders[burned_id - 1]);
			return (NULL);
		}
		else if (all_goals_met(sim))
		{
			request_stop(sim);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
