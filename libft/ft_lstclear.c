/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 07:02:39 by brportos          #+#    #+#             */
/*   Updated: 2026/02/01 10:44:41 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*top;

	if (!lst || !*lst || !del)
		return ;
	top = *lst;
	while (top)
	{
		tmp = (top)->next;
		del((top)->content);
		free(top);
		top = tmp;
	}
	*lst = NULL;
}
