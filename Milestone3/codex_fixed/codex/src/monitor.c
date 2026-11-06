/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:57 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/04 09:26:17 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	all_compiled(t_simu *simu)
{
	int	i;
	int	n;

	i = 0;
	while (i < simu->number_of_coders)
	{
		pthread_mutex_lock(&simu->coders[i].mutex_state);
		n = simu->coders[i].nb_compiles;
		pthread_mutex_unlock(&simu->coders[i].mutex_state);
		if (n < simu->number_of_compiles_required)
			return (false);
		i++;
	}
	return (true);
}

static int	check_burnout(t_simu *simu)
{
	int		i;
	long	last_compile;

	i = 0;
	while (i < simu->number_of_coders)
	{
		pthread_mutex_lock(&simu->coders[i].mutex_state);
		last_compile = simu->coders[i].last_start_compile_ms;
		pthread_mutex_unlock(&simu->coders[i].mutex_state);
		if (time_elapsed_since(last_compile) >= simu->time_to_burnout)
		{
			log_burnout(simu, simu->coders[i].id);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_simulation(t_simu *simu)
{
	if (!check_burnout(simu))
		return (0);
	if (all_compiled(simu))
	{
		stop_simulation(simu);
		return (0);
	}
	return (1);
}

void	*routine_monitor(void *arg)
{
	t_simu	*simu;

	simu = (t_simu *)arg;
	while (!simulation_is_complete(simu))
	{
		if (!check_simulation(simu))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
