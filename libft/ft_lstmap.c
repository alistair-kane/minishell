/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 01:10:54 by alkane            #+#    #+#             */
/*   Updated: 2021/12/11 19:25:39 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret_list;
	t_list	*test;

	if (!lst)
		return (NULL);
	test = ft_lstnew(f(lst->content));
	if (!test)
	{
		ft_lstclear(&ret_list, del);
		return (NULL);
	}
	ret_list = test;
	while (lst -> next != NULL)
	{
		lst = lst -> next;
		test = ft_lstnew(f(lst->content));
		ft_lstadd_back(&ret_list, test);
		test = test -> next;
	}
	return (ret_list);
}
