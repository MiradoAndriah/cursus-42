/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 09:36:32 by brportos          #+#    #+#             */
/*   Updated: 2026/02/05 17:48:11 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst && new)
	{
		*lst = new;
		return ;
	}
	if (lst && !new)
		return ;
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
