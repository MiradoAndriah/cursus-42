/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:05:31 by herinaan          #+#    #+#             */
/*   Updated: 2026/04/02 15:38:22 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	*is_array(t_stack *a, int *size)
{
	t_stack	*temp;
	int		i;
	int		*array;

	if (!a)
		return (NULL);
	i = 0;
	temp = a;
	array = malloc(sizeof(int) * (*size));
	if (!array)
		return (NULL);
	while (temp)
	{
		array[i] = temp->content;
		i++;
		temp = temp->next;
	}
	return (array);
}

static int	*is_array_sorted(t_stack *a)
{
	int	i;
	int	size;
	int	swap;
	int	*array;
	int	j;

	size = stack_size(a);
	i = 0;
	array = is_array(a, &size);
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (array[i] > array[j])
			{
				swap = array[i];
				array[i] = array[j];
				array[j] = swap;
			}
			j++;
		}
		i++;
	}
	return (array);
}

void	indexing(t_stack *a)
{
	int		i;
	int		size;
	int		*array;
	t_stack	*temp;

	size = stack_size(a);
	array = is_array_sorted(a);
	if (!array)
		return ;
	temp = a;
	while (temp)
	{
		i = 0;
		while (i < size)
		{
			if (array[i] == temp->content)
			{
				temp->index = i;
				break ;
			}
			i++;
		}
		temp = temp->next;
	}
	free(array);
}
