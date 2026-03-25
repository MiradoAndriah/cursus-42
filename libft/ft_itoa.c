/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 02:17:48 by brportos          #+#    #+#             */
/*   Updated: 2026/02/08 08:29:10 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	if (!n)
		return (1);
	len = 0;
	if (n < 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static long	ft_itoa_check(long n_tmp)
{
	long	nbr;

	if (n_tmp < 0)
		nbr = (long)-n_tmp;
	else
		nbr = (long)n_tmp;
	return (nbr);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*str;
	long	n_tmp;
	int		len;

	n_tmp = n;
	len = ft_len(n_tmp);
	str = malloc(sizeof * str * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	nbr = ft_itoa_check(n_tmp);
	while (len > 0)
	{
		str[len - 1] = (nbr % 10) + '0';
		nbr /= 10;
		len--;
		if (n_tmp < 0 && len == 1)
			break ;
	}
	if (n_tmp < 0)
		str[0] = '-';
	return (str);
}
