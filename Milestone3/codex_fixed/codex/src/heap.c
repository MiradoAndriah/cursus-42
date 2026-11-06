/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:39 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/02 11:09:41 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	parent(int i)
{
	return ((i - 1) / 2);
}

bool	less(t_heap_node a, t_heap_node b)
{
	return (a.key < b.key || (a.key == b.key && a.coder_id < b.coder_id));
}

void	heap_push(t_heap *heap, long key, int coder_id)
{
	int			i;
	t_heap_node	tmp;

	if (heap->size >= MAX_HEAP)
		return ;
	i = heap->size;
	heap->tab[i].key = key;
	heap->tab[i].coder_id = coder_id;
	heap->size++;
	while (i > 0 && less(heap->tab[i], heap->tab[parent(i)]))
	{
		tmp = heap->tab[i];
		heap->tab[i] = heap->tab[parent(i)];
		heap->tab[parent(i)] = tmp;
		i = parent(i);
	}
}

t_heap_node	heap_pop(t_heap *heap)
{
	t_heap_node	min;

	min.key = 0;
	min.coder_id = -1;
	if (heap->size == 0)
		return (min);
	min = heap->tab[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->tab[0] = heap->tab[heap->size];
		check_swap_list(heap, 0);
	}
	return (min);
}

t_heap_node	*heap_peek(t_heap *heap)
{
	if (heap->size == 0)
		return (NULL);
	return (&heap->tab[0]);
}
