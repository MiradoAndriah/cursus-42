/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:21:24 by brportos          #+#    #+#             */
/*   Updated: 2026/02/08 13:27:50 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (*s)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		s++;
	}
	return (word);
}

static char	*word_dup(char const *s, int len)
{
	int		i;
	char	*dup;

	i = 0;
	if (!s)
		return (NULL);
	dup = malloc(sizeof * dup * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_len(char const *s, char c)
{
	int	j;

	j = 0;
	while (s[j] && (s[j] != c))
		j++;
	return (j);
}

char	**ft_free(char **split, int len)
{
	while (len-- >= 0)
		free(split[len]);
	free(split);
	split = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	if (!s)
		return (NULL);
	split = malloc(sizeof * split * (count_word(s, c) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		j = ft_len(s, c);
		if (*s)
			split[i++] = word_dup(s, j);
		if (!split)
			return (ft_free(split, i));
		while (*s && (*s != c))
			s++;
	}
	split[i] = NULL;
	return (split);
}
