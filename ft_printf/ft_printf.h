/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brportos <brportos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 10:25:06 by brportos          #+#    #+#             */
/*   Updated: 2026/03/25 10:41:27 by brportos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(int fd, const char *str, ...);
void	ft_conversion(int fd, va_list *ap, char *str, int *len);
size_t	ft_strlen(const char *s);
void	ft_putaddress(int fd, void *ptr, int *len);
void	ft_putlowhex(int fd, unsigned int nbr, int *len);
void	ft_putunnbr(int fd, unsigned int nbr, int *len);
void	ft_putuphex(int fd, unsigned int nbr, int *len);
void	ft_putnbr(int fd, int nbr, int *len);
void	ft_putstr(int fd, char *str, int *len);
void	ft_putchar(int fd, char c, int *len);
void	ft_putfloat(int fd, double n, int precision, int *len);

#endif
