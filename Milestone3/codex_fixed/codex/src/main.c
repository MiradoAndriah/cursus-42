/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:52 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:09:54 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	simu_dongles(t_simu *simu, int i)
{
	long	now;

	now = get_time_ms();
	simu->dongles[i].id = i;
	simu->dongles[i].is_free = true;
	simu->dongles[i].never_used = true;
	simu->dongles[i].last_release_ms = now - simu->dongle_cooldown;
	simu->dongles[i].queue.size = 0;
	pthread_mutex_init(&simu->dongles[i].mutex, NULL);
	pthread_cond_init(&simu->dongles[i].cond, NULL);
}

static void	simu_coders(t_simu *simu, int i)
{
	long	now;

	now = get_time_ms();
	simu->coders[i].id = i + 1;
	simu->coders[i].nb_compiles = 0;
	simu->coders[i].last_start_compile_ms = now;
	simu->coders[i].simu = simu;
	simu->coders[i].dongle_left = &simu->dongles[i];
	simu->coders[i].dongle_right = &simu->dongles[(i + 1) % simu->nb_dongles];
	pthread_mutex_init(&simu->coders[i].mutex_state, NULL);
}

static void	init_simu_objects(t_simu *simu)
{
	int	i;

	pthread_mutex_init(&simu->mutex_log, NULL);
	pthread_mutex_init(&simu->mutex_stop, NULL);
	simu->simulation_complete = false;
	i = 0;
	while (i < simu->nb_dongles)
	{
		simu->dongles[i].never_used = true;
		simu_dongles(simu, i);
		i++;
	}
	i = 0;
	while (i < simu->number_of_coders)
	{
		simu_coders(simu, i);
		i++;
	}
}

static int	init_simu(t_simu *simu)
{
	simu->next_ticket = 0;
	simu->nb_dongles = simu->number_of_coders;
	simu->coders = malloc(sizeof(t_coder) * simu->number_of_coders);
	if (!simu->coders)
		return (1);
	simu->dongles = malloc(sizeof(t_dongle) * simu->nb_dongles);
	if (!simu->dongles)
	{
		free(simu->coders);
		simu->coders = NULL;
		return (1);
	}
	memset(simu->coders, 0, sizeof(t_coder) * simu->number_of_coders);
	init_simu_objects(simu);
	return (0);
}

int	main(int argc, char **argv)
{
	t_simu		simu;
	pthread_t	thread_monitor;
	int			i;

	if (!parse_args(argc, argv, &simu))
		return (1);
	init_simu(&simu);
	simu.start_time_ms = get_time_ms();
	prejoin_queues(&simu);
	i = 0;
	while (i < simu.number_of_coders)
	{
		pthread_create(&simu.coders[i].thread, NULL, routine_coder,
			&simu.coders[i]);
		i++;
	}
	pthread_create(&thread_monitor, NULL, routine_monitor, &simu);
	pthread_join(thread_monitor, NULL);
	i = 0;
	while (i < simu.number_of_coders)
	{
		pthread_join(simu.coders[i].thread, NULL);
		i++;
	}
	cleanup(&simu);
	return (0);
}
