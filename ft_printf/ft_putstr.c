/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:44:15 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 10:42:00 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(int fd, char *str, int *len)
{
	int	i;

	i = 0;
	if (!len)
		return ;
	if (!str)
	{
		ft_putstr(fd, "(null)", len);
		return ;
	}
	while (str[i])
	{
		ft_putchar(fd, str[i], len);
		i++;
	}
}
