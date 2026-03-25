/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:28:58 by herinaan          #+#    #+#             */
/*   Updated: 2026/03/25 08:27:52 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;
	int		tmp;

	if (!stack || !(*stack) || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	tmp = first->content;
	first->content = second->content;
	second->content = tmp;
}

void	sa(t_stack **a, t_stats *ops)
{
	swap(a);
	write(1, "sa\n", 3);
	if (ops)
	{
		ops->sa++;
		ops->total_ops++;
	}
}

void	sb(t_stack **b, t_stats *ops)
{
	swap(b);
	write(1, "sb\n", 3);
	if (ops)
	{
		ops->sb++;
		ops->total_ops++;
	}
}

void	ss(t_stack **a, t_stack **b, t_stats *ops)
{
	if (!a || !b || !(*a) || !(*b) || !(*a)->next || !(*b)->next)
		return ;
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
	if (ops)
	{
		ops->ss++;
		ops->total_ops++;
	}
}
