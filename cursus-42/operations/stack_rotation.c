/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:33:20 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 07:32:14 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	stack_rotation(t_stack **a)
{
	t_stack	*last;

	if (*a == NULL || (*a)->next == NULL)
		return ;
	last = *a;
	while (last->next != NULL)
		last = last->next;
	last->next = *a;
	*a = (*a)->next;
	last->next->next = NULL;
}
void	ra(t_stack **a, t_stats *ops)
{
	stack_rotation(a);
	write(1, "ra\n", 3);
	if (ops)
	{
		ops->ra++;
		ops->total_ops++;
	}
}

void	rb(t_stack **a, t_stats *ops)
{
	stack_rotation(a);
	write(1, "rb\n", 3);
	if (ops)
	{
		ops->rb++;
		ops->total_ops++;
	}
}
void	rr(t_stack **a, t_stack **b, t_stats *ops)
{
	stack_rotation(a);
	stack_rotation(b);
	write(1, "rr\n", 3);
	if (ops)
	{
		ops->rr++;
		ops->total_ops++;
	}
}
