/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:12:02 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/22 12:43:18 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	assign_dongles(t_sim *sim, int i)
{
	int	left;
	int	right;

	left = (i + sim->config.number_of_coders - 1)
		% sim->config.number_of_coders;
	right = i;
	if (left < right)
	{
		sim->coders[i].first = &sim->dongles[left];
		sim->coders[i].second = &sim->dongles[right];
	}
	else
	{
		sim->coders[i].first = &sim->dongles[right];
		sim->coders[i].second = &sim->dongles[left];
	}
}

static int	init_dongles(t_sim *sim)
{
	int	i;
	int	n;

	n = sim->config.number_of_coders;
	sim->dongles = malloc(sizeof(t_dongle) * n);
	if (!sim->dongles)
		return (1);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&sim->dongles[i].mutex, NULL);
		pthread_cond_init(&sim->dongles[i].cond, NULL);
		sim->dongles[i].is_taken = 0;
		sim->dongles[i].available_at = 0;
		memset(&sim->dongles[i].queue, 0, sizeof(t_heap));
		i++;
	}
	return (0);
}
