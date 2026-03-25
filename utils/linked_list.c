/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:37:46 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 10:27:33 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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

void	print_stack(t_stack *a)
{
	while (a != NULL)
	{
		ft_printf(1,"%d ", a->content);
		a = a->next;
	}
	ft_printf(1,"\n");
}
void	print_bench(t_stats *ops)
{
	// write(2, "[bench] disorder: ", 19);
	// ft_putfloat_fd(ops->disorder * 100, 2, 2);
	// write(2, "%\n", 2);
	ft_putstr_fd("[bench] strategy: Adaptive / O(n√n)\n", 2);
	ft_printf(2,"[bench] total_ops: %d\n", ops->total_ops);
	ft_printf(2,"[bench] sa: %d  sb: %d  ss: %d\n", ops->sa, ops->sb, ops->ss);
	ft_printf(2,"[bench] pa: %d pb: %d\n", ops->pa, ops->pb);
	ft_printf(2,"[bench] ra: %d rb: %d rr: %d\n", ops->ra, ops->rb, ops->rr);
	ft_printf(2,"[bench] rra:%d | rrb:%d | rrr:%d\n", ops->rra, ops->rrb, ops->rrr);
	write(2, "\n", 1);
}
