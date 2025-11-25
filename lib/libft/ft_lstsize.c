/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:55:57 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/18 13:29:19 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	int		i;

	i = 0;
	ptr = lst;
	if (ptr == NULL)
		return (0);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i + 1);
}
