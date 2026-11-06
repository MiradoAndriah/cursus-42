/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:09 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:09:10 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->nb_dongles)
	{
		pthread_mutex_destroy(&simu->dongles[i].mutex);
		pthread_cond_destroy(&simu->dongles[i].cond);
		i++;
	}
	i = 0;
	while (i < simu->number_of_coders)
	{
		pthread_mutex_destroy(&simu->coders[i].mutex_state);
		i++;
	}
	pthread_mutex_destroy(&simu->mutex_log);
	pthread_mutex_destroy(&simu->mutex_stop);
	free(simu->coders);
	free(simu->dongles);
}
