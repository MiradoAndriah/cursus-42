/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:23:17 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/20 12:12:54 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}					t_scheduler;

typedef struct s_config
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_scheduler		scheduler;
}					t_config;

typedef struct s_request
{
	int				coder_id;
	long			key;
}					t_request;

typedef struct s_heap
{
	t_request		*data;
	int				size;
	int				capacity;
}					t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				is_taken;
	long			available_at;
	t_heap			queue;
}					t_dongle;

struct	s_sim;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			last_compile_start;
	t_dongle		*first;
	t_dongle		*second;
	struct s_sim	*sim;
	pthread_t		thread;
}					t_coder;

typedef struct s_sim
{
	t_config		config;
	long			start_time;
	int				stop;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		monitor;
}					t_sim;

int					parsing(int ac, char **av, t_config *config);
long				get_time_ms(void);
void				smart_sleep(long ms, t_sim *sim);
int					is_stopped(t_sim *sim);
int		init_sim(t_sim *sim);
void	cleanup_sim(t_sim *sim);

#endif