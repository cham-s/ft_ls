/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 12:25:43 by cattouma          #+#    #+#             */
/*   Updated: 2015/12/01 19:18:18 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh;

	fresh = (t_list *)malloc(sizeof(t_list));
	if (!fresh)
		return (NULL);
	if (!content)
		fresh->content = NULL;
	else
	{
		fresh->content = (void *)ft_memalloc(sizeof(content_size));
		ft_memcpy(fresh->content, content, content_size);
	}
	fresh->content_size = 0;
	fresh->next = NULL;
	return (fresh);
}
