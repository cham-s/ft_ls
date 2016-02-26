/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 20:51:11 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/26 19:08:06 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <stdio.h>
#include <time.h>

void	listallfilesfree(t_file **list, t_file *entry, t_max *maxs)
{
	t_file		*tmp;
	static int	i = 0;

	if (i++ != 0)
		printdirnl(entry->pathname, false);
	if (entry->errordir && S_ISDIR(entry->fstat->st_mode))
		ft_perror(entry->filename ,entry->errordir);
	if (g_options.l && (*list)->next->next != NULL)
		printtotal(list);
	while (*list != NULL)
	{
		tmp = *list;
		if (check_for_a(*list))
		{
			*list = (*list)->next;
			//free_content_and_node(tmp);
			continue ;
		}
		if (g_options.l)
			print_l_format(*list, maxs);
		else
			printfile(*list);
		*list = (*list)->next;
		//free_content_and_node(tmp);
	}
}
void	listdir(t_file *entry)
{
	t_file	*list;
	t_max	maxs;

	list = NULL;
	initmax(&maxs);
	getfiles(entry, &list, &maxs);
	listallfilesfree(&list, entry, &maxs);
}

void	listfile(t_file *entry)
{
	t_max	maxs;

	initmax(&maxs);
	if (g_options.l)
		print_l_format(entry, &maxs);
	else
		ft_putendl(entry->filename);
}

static void	apply_recurdir(t_file **list, t_file *entry)
{
	t_file		*tmp;

	while (*list != NULL)
	{
		tmp = *list;
		if (ft_strcmp((*list)->filename, ".") == 0
		|| ft_strcmp((*list)->filename, "..") == 0)
			*list = (*list)->next;
		else
		{
			if (check_for_a(*list))
			{
				*list = (*list)->next;
				free_content_and_node(tmp);
				continue ;
			}
			if (entry->ferrno)
				ft_perror(entry->filename, entry->ferrno);
			if (S_ISDIR(entry->fstat->st_mode))
				recurdir(*list);
			*list = (*list)->next;
		}
		free_content_and_node(tmp);
	}
}

void	recurdir(t_file *entry)
{
	t_max		maxs;
	t_file		*list;

	list = NULL;
	initmax(&maxs);
	getfiles(entry, &list, &maxs);
	listallfiles(&list, entry, &maxs);
	apply_recurdir(&list, entry);
}
