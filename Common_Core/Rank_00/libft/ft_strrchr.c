/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:58:01 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/11 23:02:43 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		a;
	const char	*p;

	a = (char) c;
	p = s + ft_strlen (s);
	while (p >= s)
	{
		if (*p == a)
		{
			return ((char *) p);
		}
		p--;
	}
	return (NULL);
}
