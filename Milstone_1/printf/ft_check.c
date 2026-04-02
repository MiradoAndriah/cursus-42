/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:22:13 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/17 09:38:58 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == '%')
		return (ft_putchar('%'));
	else if (c == 'p')
		return (ft_putaddr(va_arg(args, void *)));
	else if (c == 'x')
		return (ft_puthex_low(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_puthex_uper(va_arg(args, unsigned int)));
	else if (c == 'u')
		return (ft_putnbr_unsig(va_arg(args, unsigned int)));
	return (0);
}
