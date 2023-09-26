/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:58:35 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/13 10:09:00 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*map_str;

	len = ft_strlen(s);
	map_str = (char *)malloc((len + 1) * sizeof(char));
	if (map_str == NULL)
		return (NULL);
	i = 0;
	while (i < (int)len)
	{
		map_str[i] = f((unsigned int)i, s[i]);
		i++;
	}
	map_str[len] = '\0';
	return (map_str);
}
