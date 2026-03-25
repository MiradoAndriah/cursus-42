/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:44:06 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 10:43:02 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int fd, int nbr, int *len)
{
	if (!len)
		return ;
	if (nbr == -2147483648)
		ft_putstr(fd, "-2147483648", len);
	else if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
		(*len)++;
		ft_putnbr(fd, nbr, len);
	}
	else if (nbr >= 10)
	{
		ft_putnbr(fd, nbr / 10, len);
		ft_putnbr(fd, nbr % 10, len);
	}
	else
		ft_putchar(fd, nbr + '0', len);
}
