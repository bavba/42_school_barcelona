/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricalle <aricalle@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:02:08 by aricalle          #+#    #+#             */
/*   Updated: 2023/09/13 10:10:07 by aricalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_clear_and_free_list(t_list **list, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	current = *list;
	while (current)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*list = NULL;
}

static t_list	*ft_create_new_node(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

static t_list	*ft_map_node(t_list *lst, void *(*f)(void *),
		void (*del)(void *))
{
	void	*new_content;
	t_list	*new_node;

	new_content = f(lst->content);
	if (!new_content)
		return (NULL);
	new_node = ft_create_new_node(new_content);
	if (!new_node)
	{
		del(new_content);
		return (NULL);
	}
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	new_list = NULL;
	while (lst)
	{
		new_node = ft_map_node(lst, f, del);
		if (!new_node)
		{
			ft_clear_and_free_list(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
