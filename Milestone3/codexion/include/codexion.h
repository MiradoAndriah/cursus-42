/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:24 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 13:21:14 by herinaan         ###   ########.fr       */
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

typedef struct s_params
{
	int					coder_count;
	long				time_to_burnout;
	long				time_to_compile;
	long				time_to_debug;
	long				time_to_refactor;
	int					compile_goal;
	long				dongle_cooldown;
	int					edf_mode;
}						t_params;

typedef struct s_sim	t_sim;

typedef struct s_node
{
	long				priority;
	int					id;
}						t_node;

typedef struct s_heap
{
	t_node				*nodes;
	int					size;
	int					capacity;
}						t_heap;

typedef struct s_dongle
{
	int					in_use;
	long				next_ticket;
	long				available_at;
	t_heap				waiters;
}						t_dongle;

typedef struct s_coder
{
	int					id;
	pthread_t			thread;
	t_dongle			*left_dongle;
	t_dongle			*right_dongle;
	long				last_compile_start;
	long				start_offset;
	long				next_start;
	int					compile_count;
	t_sim				*sim;
}						t_coder;

struct					s_sim
{
	t_params			params;
	long				start_time;
	long				cycle;
	int					stop_flag;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		state_mutex;
	pthread_mutex_t		queue_mutex;
	pthread_cond_t		queue_cond;
	pthread_t			monitor_thread;
};
int						parse_args(int argc, char **argv, t_params *params);
long					get_time_ms(void);
void					sleep_ms(t_sim *sim, long ms);
void					cleanup_sim(t_sim *sim);
int						init_sim(t_sim *sim, t_params *params);
void					log_event(t_coder *coder, char *msg);
void					log_burnout(t_coder *coder);
void					*coder_routine(void *arg);
int						run_simulation(t_sim *sim);
void					destroy_dongles(t_sim *sim, int count);
void					destroy_queue_sync(t_sim *sim);
void					destroy_mutexes(t_sim *sim);
int						is_stopped(t_sim *sim);
void					wake_waiters(t_sim *sim);
void					request_stop(t_sim *sim);
void					*monitor_routine(void *arg);
int						node_precedes(t_node *a, t_node *b);
void					heap_swap(t_node *a, t_node *b);
void					sift_up(t_heap *heap, int i);
void					sift_down(t_heap *heap, int i);
int						heap_init(t_heap *heap, int capacity);
void					heap_destroy(t_heap *heap);
int						heap_push(t_heap *heap, long priority, int id);
int						heap_peek_id(t_heap *heap);
void					heap_remove(t_heap *heap, int id);
int						init_queue_sync(t_sim *sim);
int						enqueue_request(t_coder *coder);
long					ready_time(t_coder *coder);
int						acquire_both_dongles(t_coder *coder);
void					release_both_dongles(t_coder *coder, long cooldown);
long					compute_cycle(t_params *params);
long					compute_offset(t_params *params, long cycle, int id);
void					wait_for_slot(t_coder *coder);
int						read_values(char **argv, long *values);
int						check_values(long *values);
int						print_error(char *msg);

#endif
