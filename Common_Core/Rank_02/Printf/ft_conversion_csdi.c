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

int	print_char(char c, int *length)
{
	if (write(1, &c, 1) == -1)
		*length = -1;
	else
		*length += 1;
	return (*length);
}

void	ft_print_string(char *str, int *length)
{
	size_t	index;

	index = 0;
	if (!str)
		str = "(NULL)";
	while (str[index] && *length != -1)
	{
		if (ft_print_char(str[index], length) == -1)
			*length = -1;
		index++;
	}	
}

void	ft_print_number(int value, int *length)
{
	unsigned int	unsigned_value;;

	if (value < 0 && *length != -1)
	{
		unsigned_value = (unsigned int) -value;
		if (ft_print_char('-', length) == -1)
			*length = -1;
	}
	else
		unsigned_value = (unsigned int) value;
	if (unsigned_value > 9 && *length != -1)
	{
		ft_print_number(unsigned_value / 10, length);
	}
	if (*length != -1 && ft_print_char((unsigned_value % 10) + '0', length) == -1)
		*length = -1;
}