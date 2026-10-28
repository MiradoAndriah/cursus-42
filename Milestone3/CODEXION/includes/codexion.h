/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:27:38 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:27:42 by herinaan         ###   ########.fr       */
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
}	t_scheduler;

typedef struct s_config
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;

typedef struct s_request
{
	int		coder_id;
	long	key;
}	t_request;

typedef struct s_heap
{
	t_request	*data;
	int			size;
	int			capacity;
}	t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				is_taken;
	long			available_at;
	long			seq;
	t_heap			queue;
}	t_dongle;

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
}	t_coder;

typedef struct s_sim
{
	t_config		config;
	long			start_time;
	int				stop;
	int				n_dongles;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		monitor;
}	t_sim;

int		parsing(int ac, char **av, t_config *conf);
long	get_time_ms(void);
void	set_abs_time(struct timespec *ts, long ms);
int		is_stopped(t_sim *sim);
void	set_stop(t_sim *sim);
void	smart_sleep(long ms, t_sim *sim);
void	log_state(t_coder *c, char *msg);
void	log_burnout(t_sim *sim, int id);
int		heap_init(t_heap *h, int capacity);
int		heap_push(t_heap *h, t_request req);
void	heap_pop(t_heap *h);
void	heap_free(t_heap *h);
int		heap_less(t_request *a, t_request *b);
void	sift_up(t_heap *h, int i);
void	sift_down(t_heap *h, int i);
int		init_sim(t_sim *sim);
int		init_dongles(t_sim *sim);
void	cleanup_sim(t_sim *sim);
int		take_dongle(t_coder *c, t_dongle *d);
void	release_dongle(t_coder *c, t_dongle *d);
void	*coder_routine(void *arg);
void	*monitor_routine(void *arg);
void	wake_all(t_sim *sim);
void	run_sim(t_sim *sim);

#endif
