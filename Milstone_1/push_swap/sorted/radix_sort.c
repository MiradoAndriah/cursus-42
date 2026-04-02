/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 09:36:08 by brportos          #+#    #+#             */
/*   Updated: 2026/04/02 16:08:23 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	get_max_bits(t_stack *a)
{
	int	max;
	int	bits;

	if (!a)
		return (0);
	max = a->index;
	while (a)
	{
		if (a->index > max)
			max = a->index;
		a = a->next;
	}
	if (max == 0)
		return (1);
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
	max_bits = get_max_bits(*a);
	i = 0;
	while (i < max_bits)
	{
		size = stack_size(*a);
		j = 0;
		while (j < size)
		{
			if ((((*a)->index >> i) & 1) == 0)
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
