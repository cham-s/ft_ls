/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:36:42 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/08 21:28:30 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/libls.h"

t_file	*ft_lstfilenew(const char *content)
{
	t_file	*fresh;
	size_t	len;

	fresh = (t_file *)malloc(sizeof(t_file));
	if (!fresh)
		return (NULL);
	if (!content)
		fresh->filename = NULL;
	else
	{
		len = ft_strlen(content);
		fresh->filename = (void *)ft_memalloc(sizeof(len));
		ft_memcpy(fresh->filename, content, len);
	}
	fresh->next = NULL;
	fresh->dirlist = NULL;
	return (fresh);
}

void	ft_lstfileappend(t_file **alst, t_file *new)
{
	t_file *current;

	current = *alst;
	if (!current)
		*alst = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	ft_lstfileprint(t_file **alst)
{
	t_file *current;

	current = *alst;
	if (!current)
		return ;
	while (current)
	{
		ft_putendl(current->filename);
		current = current->next;
	}
}
