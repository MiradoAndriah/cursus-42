/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:32:52 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 10:58:50 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *str, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			if (*(str + 1) == 32)
				return (0);
			str++;
			ft_conversion(fd, &ap, (char *)str, &len);
		}
		else
			ft_putchar(fd, *str, &len);
		str++;
	}
	va_end(ap);
	return (len);
}
