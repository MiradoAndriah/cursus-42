/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:07:49 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 08:29:06 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	find_min(t_stack *a)
{
	int	min;

	if (!a)
		return (0);
	min = a->content;
	while (a)
	{
		if (a->content < min)
			min = a->content;
		a = a->next;
	}
	return (min);
}

static void	move_min_top(t_stack **a, t_stats *ops)
{
	int	min;
	int	pos;

	min = find_min(*a);
	pos = min_position(*a);
	if (pos < stack_size(*a) / 2)
	{
		while ((*a)->content != min)
			ra(a, ops);
	}
	else
	{
		while ((*a)->content != min)
			rra(a, ops);
	}
}

void	selection_sort(t_stack **a, t_stack **b, t_stats *ops)
{
	while (stack_size(*a) > 3)
	{
		move_min_top(a, ops);
		pb(a, b, ops);
	}
	sort_three(a, ops);
	while (*b)
		pa(a, b, ops);
}
