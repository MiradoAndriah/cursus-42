/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:14:45 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 08:28:00 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	stack_size(t_stack *a)
{
	int	count;

	count = 0;
	if (!a)
		return (0);
	while (a)
	{
		count++;
		a = a->next;
	}
	return (count);
}

int	find_max(t_stack *a)
{
	int	max;

	if (!a)
		return (0);
	max = a->content;
	while (a)
	{
		if (a->content > max)
			max = a->content;
		a = a->next;
	}
	return (max);
}

int	max_position(t_stack *b)
{
	int	max;
	int	pos;
	int	i;

	max = find_max(b);
	pos = 0;
	i = 0;
	if (!b)
		return (0);
	while (b)
	{
		if (b->content == max)
		{
			pos = i;
			break ;
		}
		i++;
		b = b->next;
	}
	return (pos);
}

void	chunk_sort(t_stack **a, t_stack **b, t_stats *ops)
{
	int	size;
	int	chunk_size;

	if (!*a || is_sorted(*a) == 1)
		return ;
	size = stack_size(*a);
	chunk_size = ft_sqr(size);
	pb_chunks(a, b, chunk_size, ops);
	while (*b)
	{
		if (max_position(*b) < stack_size(*b) / 2)
		{
			while ((*b)->content != find_max(*b))
				rb(b, ops);
		}
		else
		{
			while ((*b)->content != find_max(*b))
				rrb(b, ops);
		}
		pa(a, b, ops);
	}
}
