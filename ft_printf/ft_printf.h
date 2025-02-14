/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:06:19 by ababdoul          #+#    #+#             */
/*   Updated: 2025/02/14 22:24:52 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int				ft_putchar(int c);
int				ft_putnbr(int nb);
int				ft_putstr(char *str);
int				ft_printf(const char *s, ...);
size_t			ft_strlen(const char *s);
int				convert_hex(unsigned int n);
int				print_addr(unsigned long num);
int				ft_convert_hex(unsigned int n);
unsigned int	ft_unsigned(unsigned int nb);

#endif
