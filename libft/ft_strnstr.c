/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 11:27:13 by brportos          #+#    #+#             */
/*   Updated: 2026/02/05 10:37:41 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && (i + ft_strlen(little)) <= len)
	{
		if (ft_strncmp(big + i, little, ft_strlen(little)) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
