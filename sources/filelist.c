/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 16:20:42 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/03 20:48:40 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdio.h> 

static void    addstat(struct stat *file, char *filename, t_file *new)
{
	new->filename = ft_strnew(ft_strlen(filename));
	ft_strcpy(new->filename, filename);
	new->next = NULL;
	new->date = file->st_mtime;
}

t_file	*ft_lstfilenew(char *filename)
{
	t_file *new;
	struct stat file;

	if ((new = (t_file *)ft_memalloc(sizeof(t_file))) == NULL
		|| filename == NULL)
		return (NULL);
    lstat(filename, &file);
    if (S_ISLNK(file.st_mode))
        addstat(&file, filename, new);
    else
    {
        stat(filename, &file);
        addstat(&file, filename, new);
    }
	return (new);
}

void            ft_lstfileappend(t_file **list, t_file *new)
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

void	        initmax(t_max *maxs)
{
	maxs->lnk = 0;
	maxs->size = 0;
	maxs->day = 0;
}
