#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_stats	*ops;

	// int		i;
	a = NULL;
	b = NULL;
	ops = ft_calloc(1, sizeof(t_stats));
	if (ac < 2)
		return (0);
	if (count_strategy_flags(ac, av) > 1)
		return (write(2, "error\n", 6), 1);
	isdoublequoted(&a, av);
	compute_disorder(a, ops);
	if (apply_flag_strategy(ac, av, &a, &b, ops) == 0)
		adaptive(&a, &b, ops);
	is_bench(ac, av, ops);
	print_stack(a);
	ft_stackclear(&a);
	free(ops);
}
