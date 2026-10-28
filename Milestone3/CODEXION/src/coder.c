/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:28:06 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:28:08 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	take_both(t_coder *c)
{
	if (take_dongle(c, c->first))
		return (1);
	if (take_dongle(c, c->second))
	{
		release_dongle(c, c->first);
		return (1);
	}
	return (0);
}

static void	compile(t_coder *c)
{
	long	now;

	now = get_time_ms();
	pthread_mutex_lock(&c->sim->state_mutex);
	c->last_compile_start = now;
	pthread_mutex_unlock(&c->sim->state_mutex);
	log_state(c, "is compiling");
	smart_sleep(c->sim->config.time_to_compile, c->sim);
	pthread_mutex_lock(&c->sim->state_mutex);
	c->compile_count++;
	pthread_mutex_unlock(&c->sim->state_mutex);
}

static void	rest(t_coder *c)
{
	log_state(c, "is debugging");
	smart_sleep(c->sim->config.time_to_debug, c->sim);
	log_state(c, "is refactoring");
	smart_sleep(c->sim->config.time_to_refactor, c->sim);
}

static void	*lonely_coder(t_coder *c)
{
	if (take_dongle(c, c->first) == 0)
	{
		while (!is_stopped(c->sim))
			usleep(500);
	}
	return (NULL);
}

void	*coder_routine(void *arg)
{
	t_coder	*c;

	c = (t_coder *)arg;
	if (c->first == c->second)
		return (lonely_coder(c));
	while (!is_stopped(c->sim))
	{
		if (take_both(c))
			break ;
		compile(c);
		release_dongle(c, c->first);
		release_dongle(c, c->second);
		rest(c);
	}
	return (NULL);
}
