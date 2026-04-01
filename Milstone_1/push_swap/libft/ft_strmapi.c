/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:53:52 by brportos          #+#    #+#             */
/*   Updated: 2026/02/01 10:41:33 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*strmapi;

	if (!s || !f)
		return (NULL);
	strmapi = malloc(sizeof * strmapi * ft_strlen(s) + 1);
	if (!strmapi)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		strmapi[i] = f(i, s[i]);
		i++;
	}
	strmapi[i] = '\0';
	return (strmapi);
}
