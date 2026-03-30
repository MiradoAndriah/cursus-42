/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:37:46 by brportos          #+#    #+#             */
/*   Updated: 2026/03/30 10:56:55 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	apply_flag_strategy(int ac, char **av, t_strat *strat)
{
	int		i;
	char	**split;
	int		j;

	i = 1;
	while (i < ac && av[i])
	{
		split = ft_split(av[i], ' ');
		j = 0;
		while (split[j])
		{
			if (ft_strcmp(split[j], "--simple") == 0)
				selection_sort(strat->a, strat->b, strat->ops);
			else if (ft_strcmp(split[j], "--medium") == 0)
				chunk_sort(strat->a, strat->b, strat->ops);
			else if (ft_strcmp(split[j], "--complex") == 0)
				radix_sort(strat->a, strat->b, strat->ops);
			j++;
		}
		free_split(split);
		i++;
	}
	return (0);
}

t_stack	*ft_stacknew(int content)
{
	t_stack	*node;

	node = malloc(sizeof * node);
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

static t_stack	*ft_stacklast(t_stack *lst)
{
	t_stack	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_stackadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*last;

	if (!lst && new)
	{
		*lst = new;
		return ;
	}
	if (!new && lst)
		return ;
	if (!lst && !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_stacklast(*lst);
		last->next = new;
	}
}

void	print_bench(char *str, t_stats *ops)
{
	ft_printf(2, "[bench] disorder: %f %%\n", ops->disorder * 100);
	is_strategy(str, ops);
	ft_printf(2, "[bench] total_ops: %d\n", ops->total_ops);
	ft_printf(2, "[bench] sa: %d  sb: %d  ss: %d\n", ops->sa, ops->sb, ops->ss);
	ft_printf(2, "[bench] pa: %d pb: %d\n", ops->pa, ops->pb);
	ft_printf(2, "[bench] ra: %d rb: %d rr: %d\n", ops->ra, ops->rb, ops->rr);
	ft_printf(2, "[bench] rra:%d | rrb:%d | rrr:%d\n", ops->rra, ops->rrb,
		ops->rrr);
}
