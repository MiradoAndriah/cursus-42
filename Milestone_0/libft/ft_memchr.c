/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 09:54:28 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/12 13:02:54 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ss;
	unsigned char	cc;

	i = 0;
	ss = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (ss[i] == cc)
			return ((char *)&ss[i]);
		i++;
	}
	return (NULL);
}
