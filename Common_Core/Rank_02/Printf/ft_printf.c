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

static void	ft_parse_conversion(char specifier, va_list *args, int *length)
{
	if (specifier == 'c')
		ft_print_char(va_arg(*args, int), length);
	if (specifier == 's')
		ft_print_string(va_arg(*args, char *), length);
	if (specifier == 'd' || specifier == 'i')
		ft_print_number(va_arg(*args, int), length);
	if (specifier == 'u')
		ft_print_unsigned(va_arg(*args, unsigned int), length);
	if (specifier == 'X' || specifier == 'x')
		ft_print_hex(va_arg(*args, int), length, specifier);
	if (specifier == 'p')
		ft_print_pointer(va_arg(*args, unsigned long), length);
	if (specifier == '%')
		ft_print_char('%', length);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	index;
	int		length;

	index = 0;
	length = 0;
	va_start(args, str);
	while (str[index] && length != -1)
	{
		if (str[index] == '%')
		{
			index++;
			ft_parse_conversion(str[index], &args, &length);
			index++;
		}
		else
		{
			ft_print_char(str[index], &length);
			index++;
		}
		if (length == -1)
			return (-1);
	}
	va_end(args);
	return (length);
}