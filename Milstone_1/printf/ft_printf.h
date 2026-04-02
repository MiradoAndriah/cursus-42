/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herinaan <herinaan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:13:34 by herinaan          #+#    #+#             */
/*   Updated: 2026/02/16 16:00:21 by herinaan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(char c);
int	ft_check(char c, va_list args);
int	ft_putnbr(int n);
int	ft_putstr(char *s);
int	ft_puthex_low(unsigned long n);
int	ft_putaddr(void *ptr);
int	ft_puthex_uper(unsigned long n);
int	ft_putnbr_unsig(unsigned int n);
int	ft_printf(const char *format, ...);

#endif
