/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:39:07 by spark2            #+#    #+#             */
/*   Updated: 2023/03/23 21:37:48 by spark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*cur;
	t_list	*tmp;

	if (!lst || !f)
		return (0);
	res = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		cur = ft_lstnew(tmp);
		if (!cur)
		{
			ft_lstclear(&res, del);
			free(tmp);
			return (NULL);
		}
		ft_lstadd_back(&res, cur);
		lst = lst->next;
	}
	return (res);
}
