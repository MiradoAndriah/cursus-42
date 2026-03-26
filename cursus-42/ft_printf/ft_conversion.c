/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:16:45 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 10:54:36 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putfloat(int fd, double n, int precision, int *len)
{
	long	whole;
	int		i;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	whole = (long)n;
	ft_putnbr(fd, whole, len);
	write(fd, ".", 1);
	n -= (double)whole;
	i = 0;
	while (i < precision)
	{
		n *= 10;
		ft_putchar(fd, (int)n + '0', len);
		n -= (int)n;
		i++;
	}
}

void	ft_conversion(int fd, va_list *ap, char *str, int *len)
{
	if (!len || !str || !ap)
		return ;
	if (*str == 'c')
		ft_putchar(fd, va_arg(*ap, int), len);
	else if (*str == 's')
		ft_putstr(fd, va_arg(*ap, char *), len);
	else if (*str == 'p')
		ft_putaddress(fd, va_arg(*ap, void *), len);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr(fd, (int)va_arg(*ap, int), len);
	else if (*str == 'u')
		ft_putunnbr(fd, va_arg(*ap, unsigned int), len);
	else if (*str == 'x' || *str == 'X')
	{
		if (*str == 'x')
			ft_putlowhex(fd, va_arg(*ap, unsigned int), len);
		else
			ft_putuphex(fd, va_arg(*ap, unsigned int), len);
	}
	else if (*str == 'f')
		ft_putfloat(fd, va_arg(*ap, double), 2, len);
	else if (*str == '%')
		ft_putchar(fd, *str, len);
	return ;
}
