/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:08:42 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/29 19:08:42 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_list;
	t_list	*new_obj;

	if (!lst || !del || !f)
		return (NULL);
	current = lst;
	new_list = NULL;
	while (current)
	{
		new_obj = ft_lstnew(f(current->content));
		if (!new_obj)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_obj);
		current = current->next;
	}
	return (new_list);
}
