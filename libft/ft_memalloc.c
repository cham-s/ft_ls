/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:11:23 by cattouma          #+#    #+#             */
/*   Updated: 2015/11/30 17:17:58 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t *new;
	size_t i;

	i = 0;
	new = (void *)malloc(sizeof(size_t) * size);
	if (!new)
		return (NULL);
	ft_bzero(new, size);
	return (new);
}
