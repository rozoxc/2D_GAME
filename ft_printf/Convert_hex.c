/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:57:00 by ababdoul          #+#    #+#             */
/*   Updated: 2024/11/28 16:32:36 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_hex(unsigned int n)
{
	char	*hexa;
	char	buffer[16];
	int		count;
	int		i;

	hexa = "0123456789ABCDEF";
	i = 0;
	count = 0;
	if (n == 0)
		return (ft_putchar('0'));
	while (n != 0)
	{
		buffer[i] = hexa[n % 16];
		n /= 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		count += ft_putchar(buffer[i]);
	}
	return (count);
}
