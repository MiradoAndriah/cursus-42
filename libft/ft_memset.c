/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:08:40 by brportos          #+#    #+#             */
/*   Updated: 2026/02/05 22:04:14 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_buf;
	unsigned char	val;
	size_t			i;

	s_buf = (unsigned char *)s;
	val = (unsigned char)c;
	i = 0;
	while (i < n)
		s_buf[i++] = val;
	return (s);
}
