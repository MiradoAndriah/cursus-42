#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_stats *ops;

	a = NULL;
	b = NULL;
	ops = NULL;
	if (ac < 2)
		return (0);
	if (ac == 2 && ft_strchr(av[1], ' '))
		isdoublequoted(&a, av);
	else
		isunquoted(&a, ac, av);
	if (apply_flag_strategy(ac, av, &a, &b,ops) == 0)
		adaptive(&a, &b, ops);
	print_stack(a);
	ft_stackclear(&a);
}
