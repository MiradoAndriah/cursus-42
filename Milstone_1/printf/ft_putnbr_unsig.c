/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsig.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:07:33 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/18 10:25:12 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsig(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 0 && n <= 9)
	{
		count += ft_putchar(n + '0');
	}
	else
	{
		count += ft_putnbr_unsig(n / 10);
		count += ft_putnbr_unsig(n % 10);
	}
	return (count);
}
