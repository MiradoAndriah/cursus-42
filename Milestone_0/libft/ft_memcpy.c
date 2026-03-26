/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:28:42 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/12 13:05:52 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*dest1;

	i = 0;
	src1 = (unsigned char *)src;
	dest1 = (unsigned char *)dest;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}
