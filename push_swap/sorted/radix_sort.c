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

int	get_max_bits(t_stack *a)
{
	int	max;
	int	bits;

	max = find_max(a);
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

	size = stack_size(*a);
	max_bits = get_max_bits(*a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if ((((*a)->content >> i) & 1) == 1)
				ra(a, ops);
			else
				pb(a, b, ops);
			j++;
		}
		while (*b != NULL)
			pa(a, b, ops);
		i++;
	}
}
