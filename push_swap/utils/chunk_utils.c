/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:57:46 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 08:28:55 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_sqr(int nb)
{
	int	i;

	i = 1;
	if (nb <= 0)
		return (0);
	while (i < nb / i)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (i - 1);
}

void	sort_small(t_stack **a, t_stack **b, t_stats *ops)
{
	int	size;
	int	pos;

	if (!a || !(*a) || is_sorted(*a))
		return ;
	size = stack_size(*a);
	while (size > 5)
	{
		pos = min_position(*a);
		if (pos == 0)
		{
			pb(a, b, ops);
			size--;
		}
		else if (pos <= size / 2)
			ra(a, ops);
		else
			rra(a, ops);
	}
	sort_five(a, b, ops);
	while (*b)
		pa(a, b, ops);
}

void	pb_chunks(t_stack **a, t_stack **b, int chunk_size, t_stats *ops)
{
	int	pushed;

	pushed = 0;
	while (*a)
	{
		if ((*a)->content <= pushed)
		{
			pb(a, b, ops);
			rb(b, ops);
			pushed++;
		}
		else if ((*a)->content <= pushed + chunk_size)
		{
			pb(a, b, ops);
			pushed++;
		}
		else
			ra(a, ops);
	}
}
