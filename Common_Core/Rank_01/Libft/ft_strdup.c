/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:59:50 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/11 22:51:36 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		len;

	len = ft_strlen(s);
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (new_str != NULL)
	{
		ft_memcpy(new_str, s, len + 1);
	}
	return (new_str);
}
