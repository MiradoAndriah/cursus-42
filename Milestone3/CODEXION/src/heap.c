/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:28:51 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:28:53 by herinaan         ###   ########.fr       */
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
