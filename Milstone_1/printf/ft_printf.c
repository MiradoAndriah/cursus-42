/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:34:08 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/27 14:47:32 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	ap;
	int		count;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_check(format[i], ap);
		}
		else
		{
			count += ft_putchar(format[i]);
		}
		i++;
	}
	va_end(ap);
	return (count);
}
