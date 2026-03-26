/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:58:01 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/12 13:35:09 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lens;
	size_t	lend;

	i = 0;
	lens = ft_strlen(src);
	lend = ft_strlen(dst);
	if (lend >= size)
		return (size + lens);
	while (src[i] && i < (size - lend - 1))
	{
		dst[lend + i] = src[i];
		i++;
	}
	dst[lend + i] = '\0';
	return (lend + lens);
}
