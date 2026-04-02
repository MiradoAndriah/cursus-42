/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_uper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:49:56 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/16 15:51:54 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_uper(unsigned long n)
{
	char	*base;
	int		count;

	base = "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
		count = count + ft_puthex_uper(n / 16);
	count = count + ft_putchar(base[n % 16]);
	return (count);
}
