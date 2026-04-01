/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:57:46 by brportos          #+#    #+#             */
/*   Updated: 2026/03/26 12:05:37 by herinaan         ###   ########.fr       */
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

int	is_sorted(t_stack *a)
{
	if (!a)
		return (0);
	while (a && a->next)
	{
		if (a->content > a->next->content)
			return (0);
		a = a->next;
	}
	return (1);
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

int	chunk_exists_in_a(t_stack **a, int min, int max)
{
	t_stack	*tmp;

	tmp = *a;
	while (tmp)
	{
		if (tmp->index >= min && tmp->index <= max)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	pb_chunks(t_stack **a, t_stack **b, int chunk_size, t_stats *ops)
{
	int	min;
	int	max;
	int	i;
	int	size;

	i = 0;
	size = stack_size(*a);
	chunk_size = ft_sqr(size);
	while (*a)
	{
		min = i * chunk_size;
		max = (i + 1) * chunk_size - 1;
		while (chunk_exists_in_a(a, min, max))
		{
			if ((*a)->index >= min && (*a)->index <= max)
				pb(a, b, ops);
			else
				ra(a, ops);
		}
		i++;
	}
}
