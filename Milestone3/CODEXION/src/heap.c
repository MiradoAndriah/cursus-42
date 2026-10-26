/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 10:00:00 by login             #+#    #+#             */
/*   Updated: 2026/10/26 10:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_init(t_heap *h, int capacity)
{
	h->data = malloc(sizeof(t_request) * capacity);
	if (!h->data)
		return (1);
	h->size = 0;
	h->capacity = capacity;
	return (0);
}

int	heap_push(t_heap *h, t_request req)
{
	if (h->size >= h->capacity)
		return (1);
	h->data[h->size] = req;
	h->size++;
	sift_up(h, h->size - 1);
	return (0);
}

void	heap_pop(t_heap *h)
{
	if (h->size == 0)
		return ;
	h->size--;
	h->data[0] = h->data[h->size];
	sift_down(h, 0);
}

void	heap_free(t_heap *h)
{
	free(h->data);
	h->data = NULL;
	h->size = 0;
	h->capacity = 0;
}
