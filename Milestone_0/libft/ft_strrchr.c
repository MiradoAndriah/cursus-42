/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 07:47:25 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/12 13:59:25 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		last;
	char	cc;

	i = 0;
	cc = (char)c;
	last = -1;
	while (s[i])
	{
		if (s[i] == cc)
			last = i;
		i++;
	}
	if (cc == '\0')
		return ((char *)&s[i]);
	if (last != -1)
		return ((char *)&s[last]);
	return (NULL);
}
