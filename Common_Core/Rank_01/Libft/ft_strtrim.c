/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:57:50 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/11 22:55:55 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start;
	int		end;
	int		trim_len;
	char	*trim_str;

	len = ft_strlen(s1);
	start = 0;
	end = len - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	trim_len = end - start + 1;
	trim_str = (char *)malloc((trim_len + 1) * sizeof(char));
	if (trim_str == NULL)
		return (NULL);
	ft_memcpy(trim_str, s1 + start, trim_len);
	trim_str[trim_len] = '\0';
	return (trim_str);
}
