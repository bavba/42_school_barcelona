/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:00:13 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/11 22:50:42 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_substr(const char *s, char c)
{
	unsigned int	num;

	num = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			num++;
		while (*s && *s != c)
			s++;
	}
	return (num);
}

static char	**ft_free_split_array(char **split_str, unsigned int i)
{
	while (i > 0)
	{
		free(split_str[i - 1]);
		i--;
	}
	free(split_str);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	unsigned int		i;
	const char			*start_substr;
	char				**split_str;

	split_str = ft_calloc(ft_count_substr(s, c) + 1, sizeof(char *));
	if (!s || !split_str)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start_substr = s;
			while (*s && *s != c)
				s++;
			split_str[i] = ft_substr(start_substr, 0, s - start_substr);
			if (!split_str[i])
				return (ft_free_split_array(split_str, i));
			i++;
		}
	}
	return (split_str);
}
