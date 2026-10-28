/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:28:20 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:28:23 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_one_dongle(t_dongle *d)
{
	memset(d, 0, sizeof(t_dongle));
	if (heap_init(&d->queue, 2))
		return (1);
	if (pthread_mutex_init(&d->mutex, NULL))
	{
		heap_free(&d->queue);
		return (1);
	}
	if (pthread_cond_init(&d->cond, NULL))
	{
		pthread_mutex_destroy(&d->mutex);
		heap_free(&d->queue);
		return (1);
	}
	return (0);
}

int	init_dongles(t_sim *sim)
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
		if (init_one_dongle(&sim->dongles[i]))
			return (1);
		sim->n_dongles++;
		i++;
	}
	return (0);
}
