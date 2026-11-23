/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_heap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 11:09:39 by herinaan          #+#    #+#             */
/*   Updated: 2026/11/23 10:08:18 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_init(t_heap *heap, int capacity)
{
	heap->size = 0;
	heap->capacity = capacity;
	heap->nodes = malloc(sizeof(t_node) * capacity);
	if (!heap->nodes)
		return (1);
	return (0);
}

void	heap_destroy(t_heap *heap)
{
	free(heap->nodes);
	heap->nodes = NULL;
	heap->size = 0;
}

int	heap_push(t_heap *heap, long priority, int id)
{
	if (heap->size >= heap->capacity)
		return (1);
	heap->nodes[heap->size].priority = priority;
	heap->nodes[heap->size].id = id;
	heap->size++;
	sift_up(heap, heap->size - 1);
	return (0);
}

int	heap_peek_id(t_heap *heap)
{
	if (heap->size == 0)
		return (0);
	return (heap->nodes[0].id);
}

void	heap_remove(t_heap *heap, int id)
{
	int	i;

	i = 0;
	while (i < heap->size && heap->nodes[i].id != id)
		i++;
	if (i == heap->size)
		return ;
	heap->size--;
	if (i == heap->size)
		return ;
	heap->nodes[i] = heap->nodes[heap->size];
	sift_up(heap, i);
	sift_down(heap, i);
}
