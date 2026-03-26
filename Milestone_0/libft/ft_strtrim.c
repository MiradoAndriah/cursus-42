/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 08:32:16 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/12 14:35:05 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_verified(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	start = 0;
	while (s1[start] && ft_verified(s1[start], set) == 1)
		start++;
	end = ft_strlen(s1);
	while (s1[end - 1] && ft_verified(s1[end - 1], set))
		end--;
	str = ft_substr(s1, start, end - start);
	return (str);
}
