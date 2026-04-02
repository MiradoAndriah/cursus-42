/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 09:36:08 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 08:29:03 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	get_index_max(t_stack *a)
{
	int	max;
	int	index;
	int	i;

	if (!a)
		return (0);
	max = find_max(a);
	index = 0;
	i = 0;
	while (a)
	{
		if (a->content == max)
			index = i;
		i++;
		a = a->next;
	}
	return (index);
}

int	get_max_bits(t_stack *a)
{
	int	max;
	int	bits;

	max = get_index_max(a);
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	radix_sort(t_stack **a, t_stack **b, t_stats *ops)
{
	int	size;
	int	max_bits;
	int	i;
	int	j;

	if (is_sorted(*a) == 1)
		return ;
	size = stack_size(*a);
	max_bits = get_max_bits(*a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if ((((*a)->content >> i) & 1) == 0)
				pb(a, b, ops);
			else
				ra(a, ops);
			j++;
		}
		while (*b)
			pa(a, b, ops);
		i++;
	}
}
