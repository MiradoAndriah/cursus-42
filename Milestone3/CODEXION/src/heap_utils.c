/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:28:43 by herinaan          #+#    #+#             */
/*   Updated: 2026/10/27 09:28:45 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	swap_req(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	heap_less(t_request *a, t_request *b)
{
	if (a->key != b->key)
		return (a->key < b->key);
	return (a->coder_id < b->coder_id);
}

void	sift_up(t_heap *h, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!heap_less(&h->data[i], &h->data[parent]))
			break ;
		swap_req(&h->data[i], &h->data[parent]);
		i = parent;
	}
}

void	sift_down(t_heap *h, int i)
{
	int	small;
	int	l;
	int	r;

	while (1)
	{
		l = 2 * i + 1;
		r = 2 * i + 2;
		small = i;
		if (l < h->size && heap_less(&h->data[l], &h->data[small]))
			small = l;
		if (r < h->size && heap_less(&h->data[r], &h->data[small]))
			small = r;
		if (small == i)
			break ;
		swap_req(&h->data[i], &h->data[small]);
		i = small;
	}
}
