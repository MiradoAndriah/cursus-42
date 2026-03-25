/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:31:17 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 08:29:45 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

double	compute_disorder(t_stack *a)
{
	int	mistakes;
	int	total_pairs;

	mistakes = 0;
	total_pairs = 0;
	if (!a)
		return (0);
	while (a && a->next)
	{
		if (a->content > a->next->content)
			mistakes++;
		total_pairs++;
		a = a->next;
	}
	return ((double)mistakes / total_pairs);
}

void	sort_three(t_stack **a, t_stats *ops)
{
	int	first;
	int	second;
	int	third;

	if (!a || !(*a) || !(*a)->next || !(*a)->next->next)
		return ;
	first = (*a)->content;
	second = (*a)->next->content;
	third = (*a)->next->next->content;
	if (first > second && second < third && third > first)
		sa(a, ops);
	else if (first > second && second > third)
	{
		ra(a, ops);
		sa(a, ops);
	}
	else if (first > second && second < third && third < first)
		ra(a, ops);
	else if (first < second && second > third && first < third)
	{
		sa(a, ops);
		ra(a, ops);
	}
	else if (first < second && second > third && first > third)
		rra(a, ops);
}

int	min_position(t_stack *a)
{
	int	min;
	int	pos;
	int	i;

	min = find_min(a);
	pos = 0;
	i = 0;
	if (!a)
		return (0);
	while (a)
	{
		if (a->content == min)
		{
			pos = i;
			break ;
		}
		i++;
		a = a->next;
	}
	return (pos);
}

void	sort_five(t_stack **a, t_stack **b, t_stats *ops)
{
	int	pos;

	if (!a || !(*a))
		return ;
	if (is_sorted(*a) == 1)
		return ;
	while (stack_size(*a) > 3)
	{
		pos = min_position(*a);
		if (pos == 0)
			pb(a, b, ops);
		else if (pos <= stack_size(*a) / 2)
			ra(a, ops);
		else
			rra(a, ops);
	}
	sort_three(a, ops);
	pa(a, b, ops);
	pa(a, b, ops);
}

void	adaptive(t_stack **a, t_stack **b, t_stats *ops)
{
	double		disorder;
	int			size;



	size = stack_size(*a);
	if (repetition_numbers(*a))
		return (write(2, "Error\n", 6), exit(1));
	if (is_sorted(*a) == 1)
		return ;
	if (size == 2)
		ra(a, ops);
	if (size == 3)
		return (sort_three(a, ops));
	if (size > 3 && size <= 5)
		return (sort_five(a, b, ops));
	if (size <= 15)
		return (sort_small(a, b, ops));
	disorder = compute_disorder(*a);
	if (disorder < 0.2)
		selection_sort(a, b, ops);
	else if (disorder >= 0.2 && disorder < 0.5)
		chunk_sort(a, b,ops);
	else
		radix_sort(a, b,ops);
}
