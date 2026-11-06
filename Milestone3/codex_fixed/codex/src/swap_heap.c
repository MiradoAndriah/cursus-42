/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:10:24 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:10:25 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	check_swap_list(t_heap *heap, int i)
{
	int			smallest;
	int			left;
	int			right;
	t_heap_node	tmp;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		smallest = i;
		if (left < heap->size && less(heap->tab[left], heap->tab[smallest]))
			smallest = left;
		if (right < heap->size && less(heap->tab[right], heap->tab[smallest]))
			smallest = right;
		if (smallest == i)
			break ;
		tmp = heap->tab[i];
		heap->tab[i] = heap->tab[smallest];
		heap->tab[smallest] = tmp;
		i = smallest;
	}
}
