/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 20:51:11 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/22 09:41:04 by cattouma         ###   ########.fr       */
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

void	listallfilesfree(t_file **list, char *dir, t_max *maxs)
{
	t_file		*tmp;
	static int	i = 0;

	if (i++ != 0)
		printdirnl(dir, false);
	if (g_options.l && (*list)->next->next != NULL)
		printtotal(list);
	while (*list != NULL)
	{
		tmp = *list;
		if (check_for_a(*list))
		{
			*list = (*list)->next;
			free_content_and_node(tmp);
			continue ;
		}
		if (g_options.l)
			print_l_format((*list)->filename, maxs, false);
		else
			printfile(TRIM((*list)->filename));
		*list = (*list)->next;
		free_content_and_node(tmp);
	}
}

void	listdir(char *dir)
{
	t_file	*list;
	t_max	maxs;

	list = NULL;
	initmax(&maxs);
	getfiles(dir, &list, &maxs);
	listallfilesfree(&list, dir, &maxs);
}

void	listfile(char *filename)
{
	t_max	maxs;

	initmax(&maxs);
	if (g_options.l)
		print_l_format(filename, &maxs, true);
	else
		ft_putendl(filename);
}

void	apply_recurdir(t_file **list, struct stat *file)
{
	t_file		*tmp;

	while (*list != NULL)
	{
		tmp = *list;
		if (ft_strcmp(TRIM((*list)->filename), ".") == 0
		|| ft_strcmp(TRIM((*list)->filename), "..") == 0)
			*list = (*list)->next;
		else
		{
			if (check_for_a(*list))
			{
				*list = (*list)->next;
				free_content_and_node(tmp);
				continue ;
			}
			if (stat((*list)->filename, file) < 0)
				if (lstat((*list)->filename, file) < 0)
					ft_perror((*list)->filename);
			if (S_ISDIR(file->st_mode))
				recurdir((*list)->filename);
			*list = (*list)->next;
		}
		free_content_and_node(tmp);
	}
}

void	recurdir(char *dir)
{
	t_file		*list;
	struct stat	file;
	t_max		maxs;

	list = NULL;
	initmax(&maxs);
	getfiles(dir, &list, &maxs);
	listallfiles(&list, dir, &maxs);
	apply_recurdir(&list, &file);
}
