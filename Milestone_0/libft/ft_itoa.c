/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:58:03 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/09 09:35:04 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*dest;
	long	nb;

	nb = n;
	count = count_size(n);
	dest = malloc(sizeof(char) * count + 1);
	if (!dest)
		return (NULL);
	dest[count] = '\0';
	if (nb < 0)
		nb = -nb;
	if (nb == 0)
		dest[0] = '0';
	while (nb > 0)
	{
		count--;
		dest[count] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}
