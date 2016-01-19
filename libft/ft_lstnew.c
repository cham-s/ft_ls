/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 12:25:43 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/14 15:41:03 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh;

	fresh = (t_list *)malloc(sizeof(t_list));
	if (!fresh)
		return (NULL);
	if (content == NULL)
    {
		fresh->content = NULL;
        fresh->content_size = 0;
    }
	else
	{
		fresh->content = (void *)ft_memalloc(content_size);
		ft_memcpy(fresh->content, content, content_size);
        fresh->content_size = content_size;
	}
	fresh->next = NULL;
	return (fresh);
}
