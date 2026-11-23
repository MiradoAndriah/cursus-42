/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 10:13:08 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 14:39:12 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	compute_cycle(t_params *params)
{
	long	slot;
	long	half;
	long	cycle;

	if (params->coder_count < 4)
		return (0);
	slot = params->time_to_compile + params->dongle_cooldown;
	half = params->coder_count / 2;
	cycle = 2 * slot;
	if (params->coder_count % 2 == 1)
		cycle = params->coder_count * ((slot + half - 1) / half);
	if (cycle >= params->time_to_burnout)
		return (0);
	return (cycle);
}

long	compute_offset(t_params *params, long cycle, int id)
{
	long	slot;
	long	half;

	if (cycle == 0)
		return (0);
	slot = params->time_to_compile + params->dongle_cooldown;
	half = params->coder_count / 2;
	if (params->coder_count % 2 == 0)
	{
		if (id % 2 == 0)
			return (slot);
		return (0);
	}
	return (((half * (id - 1)) % params->coder_count) * (cycle
			/ params->coder_count));
}

void	wait_for_slot(t_coder *coder)
{
	long	now;

	now = get_time_ms();
	if (coder->next_start > now)
		sleep_ms(coder->sim, coder->next_start - now);
}
