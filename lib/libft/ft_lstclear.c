/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:56:39 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/18 14:04:07 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*temp;

	if (*lst == NULL)
		return ;
	ptr = *lst;
	while (ptr->next != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		ft_lstdelone(temp, del);
	}
	ft_lstdelone(ptr, del);
	*lst = NULL;
}
