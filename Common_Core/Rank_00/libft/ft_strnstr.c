/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:58:12 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/13 10:07:03 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big_s, const char *small_s, size_t len)
{
	unsigned int		i;
	unsigned int		j;
	size_t				new_len;
	char				*new_big;

	i = 0;
	j = 0;
	new_big = (char *)big_s;
	new_len = (unsigned int)len;
	if (!(*small_s))
		return (new_big);
	while (new_big[i] != '\0' && i <= new_len - 1 && len != 0)
	{
		while ((small_s[j] == new_big[i + j])
			&& new_big[i + j] != '\0' && (i + j) <= new_len - 1)
			j++;
		if (small_s[j] == '\0')
			return (new_big + i);
		j = 0;
		i++;
	}
	return (0);
}
