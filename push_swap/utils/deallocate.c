/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:13:48 by brportos          #+#    #+#             */
/*   Updated: 2026/03/20 07:17:42 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_stackclear(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = NULL;
		*stack = tmp;
	}
}

int	repetition_numbers(t_stack *a)
{
	t_stack	*j;

	while (a)
	{
		j = a->next;
		while (j)
		{
			if (a->content == j->content)
				return (1);
			j = j->next;
		}
		a = a->next;
	}
	return (0);
}
