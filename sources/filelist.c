/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 11:54:36 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/22 18:17:56 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>

void	ft_lstfileappend(t_file **list, t_file *new)
{
	t_file *current;

	current = *list;
	if (current == NULL)
		*list = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

t_file	*ft_lstfilenew(char *pathname)
{
	t_file		*new;

	new = (t_file *)ft_memalloc(sizeof(t_file));
	if (!new || !pathname)
		return (NULL);
	new->fstat = ft_memalloc(sizeof(struct stat));
	new->ferrno = 0;
	if (lstat(pathname, new->fstat) < 0)
	{
		new->ferrno = errno;
		if (stat(pathname, new->fstat) < 0)
			new->ferrno = errno;
	}
	addstat(pathname, new);
	return (new);
}

void	addstat(char *pathname, t_file *new)
{
	new->pathname = ft_strdup(pathname);
	if (ft_strrchr(pathname, '/'))
		new->filename = ft_strdup(TRIM(pathname)); 
	else
		new->filename = ft_strdup(pathname);
	new->next = NULL;
}

void	initmax(t_max *maxs)
{
	maxs->lnk = 0;
	maxs->user = 0;
	maxs->group = 0;
	maxs->uid = 0;
	maxs->gid = 0;
	maxs->minor = 0;
	maxs->major = 0;
	maxs->size = 0;
}
