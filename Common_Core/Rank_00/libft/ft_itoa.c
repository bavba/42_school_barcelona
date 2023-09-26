/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:03:15 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/13 10:09:32 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_num_len(int n)
{
	int	len;

	len = (n <= 0);
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	ft_fill_num_str(char *num_str, int n, int num_len, int sign)
{
	if (n == 0)
	{
		num_str[0] = '0';
		return ;
	}
	if (sign == -1)
		num_str[0] = '-';
	while (n != 0)
	{
		num_str[--num_len] = '0' + (sign * (n % 10));
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*num_str;
	int		num_len;
	int		sign;

	num_len = ft_get_num_len(n);
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	num_str = (char *)malloc((num_len + 1) * sizeof(char));
	if (num_str == NULL)
		return (NULL);
	num_str[num_len] = '\0';
	ft_fill_num_str(num_str, n, num_len, sign);
	return (num_str);
}
