/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:17:14 by skirwan           #+#    #+#             */
/*   Updated: 2025/05/01 13:18:35 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnewint(int num)
{
	t_list	*node;

	node = malloc(sizeof(*node));
	node->nbr = num;
	node->next = NULL;
	return (node);
}
