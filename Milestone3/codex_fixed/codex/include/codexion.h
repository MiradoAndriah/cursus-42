/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:24 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:09:26 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_HEAP 4096

typedef struct s_heap_node
{
	long				key;
	int					coder_id;
}						t_heap_node;

typedef struct s_heap
{
	t_heap_node			tab[MAX_HEAP];
	int					size;
}						t_heap;

typedef struct s_dongle
{
	int					id;
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
	bool				is_free;
	bool				never_used;
	long				last_release_ms;
	t_heap				queue;
}						t_dongle;

typedef struct s_simu	t_simu;

typedef struct s_coder
{
	int					id;
	long				last_start_compile_ms;
	int					nb_compiles;
	bool				queued;
	pthread_mutex_t		mutex_state;
	t_dongle			*dongle_left;
	t_dongle			*dongle_right;
	t_simu				*simu;
	pthread_t			thread;
}						t_coder;

struct					s_simu
{
	t_coder				*coders;
	t_dongle			*dongles;

	int					nb_dongles;
	int					stop;
	int					number_of_coders;
	long				time_to_burnout;
	long				time_to_compile;
	long				time_to_debug;
	long				time_to_refactor;
	int					number_of_compiles_required;
	long				dongle_cooldown;
	char				scheduler[8];
	bool				simulation_complete;
	pthread_mutex_t		mutex_log;
	pthread_mutex_t		mutex_stop;
	long				next_ticket;
	long				start_time_ms;
};

bool					parse_args(int argc, char **argv, t_simu *simu);
bool					all_compiled(t_simu *simu);
bool					less(t_heap_node a, t_heap_node b);
bool					check_numbers(char **argv, long *values);
bool					is_valid_number(char *str);
bool					parse_number(int arg, char **argv, long *values);

long					get_time_ms(void);
long					time_elapsed_since(long t);
long					ft_atol(const char *str);
bool					simulation_is_complete(t_simu *simu);
bool					heap_is_empty(t_heap *heap);
void					stop_simulation(t_simu *simu);
bool					try_take(t_dongle *a, t_dongle *b, int id,
							t_simu *simu);
bool					can_take(t_dongle *d, int id, t_simu *simu);
void					check_in(t_simu *simu);
void					check_swap_list(t_heap *heap, int i);

void					heap_push(t_heap *heap, long key, int coder_id);
t_heap_node				heap_pop(t_heap *heap);
t_heap_node				*heap_peek(t_heap *heap);
bool					heap_is_empty(t_heap *heap);

int						request_dongles(t_coder *c, long key);
char					*cpy(char *s1, const char *s2);
void					release_dongle(t_dongle *dongle);

long					calculate_priority_key(t_simu *simu, t_coder *coder);
long					start_delay(t_simu *simu, int id);
void					prejoin_queues(t_simu *simu);

void					log_action(t_simu *simu, int coder_id, char *message);

void					log_burnout(t_simu *simu, int coder_id);

void					*routine_coder(void *arg);

void					*routine_monitor(void *arg);

void					cleanup(t_simu *simu);

#endif
