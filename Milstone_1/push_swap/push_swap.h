/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:25:31 by brportos          #+#    #+#             */
/*   Updated: 2026/03/30 10:56:08 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				content;
	int				index;
	struct s_stack	*next;
}					t_stack;

typedef struct s_stats
{
	double			disorder;
	int				sa;
	int				sb;
	int				ss;
	int				pa;
	int				pb;
	int				ra;
	int				rb;
	int				rr;
	int				rra;
	int				rrb;
	int				rrr;
	int				total_ops;
}					t_stats;

typedef struct s_strat
{
	t_stack			**a;
	t_stack			**b;
	t_stats			*ops;
}					t_strat;

void				pa(t_stack **a, t_stack **b, t_stats *ops);
void				pb(t_stack **a, t_stack **b, t_stats *ops);
void				ra(t_stack **a, t_stats *ops);
void				rb(t_stack **a, t_stats *ops);
void				rr(t_stack **a, t_stack **b, t_stats *ops);

void				rra(t_stack **a, t_stats *ops);
void				rrb(t_stack **a, t_stats *ops);
void				rrr(t_stack **a, t_stack **b, t_stats *ops);

void				sa(t_stack **a, t_stats *ops);
void				sb(t_stack **b, t_stats *ops);
void				ss(t_stack **a, t_stack **b, t_stats *ops);

void				selection_sort(t_stack **a, t_stack **b, t_stats *ops);

void				pb_chunks(t_stack **a, t_stack **b, int chunk_size,
						t_stats *ops);
int					stack_size(t_stack *a);
int					find_max(t_stack *a);
int					ft_sqr(int nb);
void				chunk_sort(t_stack **a, t_stack **b, t_stats *ops);
char				**ft_split(char const *s, char c);
void				radix_sort(t_stack **a, t_stack **b, t_stats *ops);
double				compute_disorder(t_stack *a, t_stats *ops);
t_stack				*ft_stacknew(int content);
void				ft_stackadd_back(t_stack **lst, t_stack *new);
void				adaptive(t_stack **a, t_stack **b, t_stats *ops);
int					min_position(t_stack *a);
int					find_min(t_stack *a);
int					is_sorted(t_stack *a);
int					repetition_numbers(t_stack *a);
void				sort_three(t_stack **a, t_stats *ops);
void				sort_five(t_stack **a, t_stack **b, t_stats *ops);
void				ft_stackclear(t_stack **a);
void				isdoublequoted(t_stack **a, char **av);
void				sort_small(t_stack **a, t_stack **b, t_stats *ops);
int					apply_flag_strategy(int ac, char **av, t_strat *strat);
int					is_flags(char *str);
int					count_strategy_flags(int ac, char **av);
int					count_bench_flags(int ac, char **av);
void				print_bench(char *str, t_stats *ops);
void				is_bench(int argc, char **argv, t_stats *ops);
void				is_strategy(char *str, t_stats *ops);
void				free_split(char **split);

#endif