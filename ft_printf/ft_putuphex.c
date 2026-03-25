/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuphex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:44:02 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 10:41:52 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putuphex(int fd, unsigned int nbr, int *len)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (!len)
		return ;
	if (nbr > 15)
		ft_putuphex(fd, nbr / 16, len);
	ft_putchar(fd, base[nbr % 16], len);
}
