/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:31:28 by herinaan          #+#    #+#             */
/*   Updated: 2026/04/02 15:36:23 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_stats	*ops;
	t_strat	strat;

	a = NULL;
	b = NULL;
	if (ac < 2)
		return (0);
	if (count_strategy_flags(ac, av) > 1 || count_bench_flags(ac, av) > 1)
		return (write(2, "error\n", 6), 1);
	isdoublequoted(&a, av);
	indexing(a);
	ops = malloc(sizeof(t_stats));
	strat.a = &a;
	strat.b = &b;
	strat.ops = ops;
	compute_disorder(a, ops);
	if (apply_flag_strategy(ac, av, &strat) == 0)
		adaptive(&a, &b, ops);
	is_bench(ac, av, ops);
	ft_stackclear(&a);
	ft_stackclear(&b);
	free(ops);
}
