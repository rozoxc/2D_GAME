/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:59:02 by ababdoul          #+#    #+#             */
/*   Updated: 2024/12/02 16:22:00 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_format(const char *s, int *i, va_list args)
{
	int	count;

	count = 0;
	if (s[*i] == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (s[*i] == 'd' || s[*i] == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (s[*i] == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (s[*i] == 'p')
		count += print_addr(va_arg(args, unsigned long));
	else if (s[*i] == 'x')
		count += convert_hex(va_arg(args, unsigned int));
	else if (s[*i] == 'X')
		count += ft_convert_hex(va_arg(args, unsigned int));
	else if (s[*i] == 'u')
		count += ft_unsigned(va_arg(args, unsigned int));
	else if (s[*i] == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;
	int		count;

	count = 0;
	va_start(args, s);
	i = 0;
	if (write(1, 0, 0) == -1)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			count += handle_format(s, &i, args);
		}
		else
			count += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (count);
}
