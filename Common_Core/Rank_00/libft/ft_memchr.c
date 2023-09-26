/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:01:47 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/11 22:47:20 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		value;

	p = (const unsigned char *)s;
	value = (unsigned char)c;
	while (n > 0)
	{
		if (*p == value)
			return ((void *)p);
		p++;
		n--;
	}
	return (NULL);
}
