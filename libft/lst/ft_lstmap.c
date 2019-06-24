/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:44:31 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/24 14:25:53 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	if (!(new = f(ft_lstnew(lst->content, lst->content_size))))
		return (NULL);
	if (lst->next)
		new->next = ft_lstmap(lst->next, f);
	return (new);
}
