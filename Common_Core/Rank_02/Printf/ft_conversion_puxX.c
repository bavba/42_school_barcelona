/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:10:26 by aricalle          #+#    #+#             */
/*   Updated: 2023/11/28 12:01:07 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_unsigned(unsigned int num, int *length)
{
	if (num > 9 && *length != -1)
	{
		ft_print_number(num / 10, length);
	}	
	if (*length!= -1 && ft_print_char((num% 10) + '0', length) == -1)
		*length = -1;
}

void	ft_print_hex(int num, int *length, char format)
{
	unsigned int	number;
	char			*hex_up_case;
	char			*hex_low_case;

	hex_up_case = "0123456789ABCDEF";
	hex_low_case= "0123456789abcdef";
	number = (unsigned int) num;
	if (number >= 16 && *length != -1)
		ft_print_hex(number / 16, length, format);
	if (format == 'X')
	{
		if (*length != -1 && ft_print_char(hex_up_case[number % 16], length) == -1)
			*length = -1;
	}
	if (format == 'x')
	{
		if (*length != -1 && ft_print_char(hex_low_case[number % 16], length) == -1)
			*length = -1;
	}
}

static void	ft_print_pointer_hex(unsigned long ptr, int *length)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (*length != -1)
	{
		if (ptr >= 16 && *length != -1)
			ft_print_pointer_hex(ptr / 16, length);
		if (*length != -1 && ft_print_char(hex[ptr % 16], length) == -1)
			*length = -1;
	}
}

void	ft_print_pointer(unsigned long ptr, int *length)
{
	ft_print_string("0x", length);
	ft_print_pointer_hex(ptr, length);
}