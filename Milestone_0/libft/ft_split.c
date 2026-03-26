/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:00:58 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/12 13:22:40 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(const char *s, char c)
{
	size_t	i;
	int		trigger;
	int		count;

	i = 0;
	trigger = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (s[i] == c)
			trigger = 0;
		i++;
	}
	return (count);
}

static void	*ft_free(char **s, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	i;
	size_t	j;
	size_t	start;

	start = 0;
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	while (s[i] && j < ft_count_word(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		dest[j] = ft_substr(s, start, i - start);
		if (!(dest[j]))
			return (ft_free(dest, j));
		j++;
	}
	dest[j] = NULL;
	return (dest);
}
