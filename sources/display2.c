/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 14:32:15 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/17 14:36:10 by cattouma         ###   ########.fr       */
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

void	listallfilesfree(t_file **list, char *directory, char *options, t_max *maxs)
{
	t_file		*tmp;
	static int	i = 0;

	if (i++ != 0)
		printdirnl(directory, false);
	if (ft_strchr(options, 'l') && (*list)->next->next != NULL)
		printtotal(list, options);
	while (*list != NULL)
	{
		tmp = *list;
		if (ft_strchr(options, 'a') == NULL && pathtrim((*list)->filename)[0] == '.')
		{
			*list = (*list)->next;
			free(tmp->filename);
			free(tmp);
			continue ;
		}
		if (ft_strchr(options, 'l'))
			print_l_format((*list)->filename, maxs, false);
		else
			printfile(pathtrim((*list)->filename), options);
		*list = (*list)->next;
		free(tmp->filename);
		free(tmp);
	}
}

void	listdir(char *directory, char *options)
{
	t_file	*list;
	t_max	maxs;

	list = NULL;
	initmax(&maxs);
	getfiles(directory, &list, options, &maxs);
	listallfilesfree(&list, directory, options, &maxs);
}

void	listfile(char *filename, char *options)
{
	t_max	maxs;

	initmax(&maxs);
	if (ft_strchr(options, 'l'))
		print_l_format(filename, &maxs, true);
	else
		ft_putendl(filename);
}

void	printfile(char *fname, char *options)
{
	if (ft_strchr(options, 'l') == NULL)
		ft_putendl(fname);
}

void	recurdir(char *directory, char *options)
{
	t_file		*list;
	t_file		*tmp;
	struct stat	file;
	t_max		maxs;

	list = NULL;
	initmax(&maxs);
	getfiles(directory, &list, options, &maxs);
	listallfiles(&list, options, directory, &maxs);
	while (list != NULL)
	{
		tmp = list;
		if (ft_strcmp(pathtrim(list->filename), ".") == 0
		|| ft_strcmp(pathtrim(list->filename), "..") == 0)
			list = list->next;
		else
		{
			//skip dots todo function
			if (ft_strchr(options, 'a') == NULL && pathtrim(list->filename)[0] == '.')
			{
				list = list->next;
				free(tmp->filename);
				free(tmp);
				continue ;
			}
			if(stat(list->filename, &file) < 0)
				if(lstat(list->filename, &file) < 0)
					ft_perror(list->filename);
			if (S_ISDIR(file.st_mode))
				recurdir(list->filename, options);
			list = list->next;
		}
		free(tmp->filename);
		free(tmp);
	}
}
