/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:37:46 by brportos          #+#    #+#             */
/*   Updated: 2026/03/31 11:29:24 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	apply_flag_strategy(int ac, char **av, t_strat *strat)
{
	char	**split;
	int		j;

	if (repetition_numbers(*strat->a))
		return (ft_stackclear(strat->a), write(2, "error\n", 6),
			free(strat->ops), exit(1), 0);
	while (--ac && *++av)
	{
		split = ft_split(*av, ' ');
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
	}
	return (0);
}

t_stack	*ft_stacknew(int content)
{
	t_stack	*node;

	node = malloc(sizeof *node);
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
	if (!new &&lst)
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
	ft_printf(2, "[bench] sa: %d sb: %d ss: %d pa: %d pb: %d\n", ops->sa,
		ops->sb, ops->ss, ops->pa, ops->pb);
	ft_printf(2, "[bench] ra: %d rb: %d rr: %d rra:%d rrb:%d rrr:%d\n", ops->ra,
		ops->rb, ops->rr, ops->rra, ops->rrb, ops->rrr);
}
