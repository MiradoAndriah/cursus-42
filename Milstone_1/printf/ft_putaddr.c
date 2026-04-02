/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:46:29 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/18 10:29:00 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putaddr(void *ptr)
{
	unsigned long	addr;
	int				count;

	count = 0;
	addr = (unsigned long)ptr;
	if (!ptr)
	{
		count += ft_putstr("(nil)");
		return (count);
	}
	count += ft_putstr("0x");
	count += ft_puthex_low(addr);
	return (count);
}
