/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:44:19 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 10:41:57 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunnbr(int fd, unsigned int nbr, int *len)
{
	if (!len)
		return ;
	if (nbr >= 10)
	{
		ft_putunnbr(fd, nbr / 10, len);
		ft_putunnbr(fd, nbr % 10, len);
	}
	else
		ft_putchar(fd, nbr + '0', len);
}
