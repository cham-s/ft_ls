/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 14:31:36 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/22 17:22:15 by cattouma         ###   ########.fr       */
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
#include <errno.h>

void		apply_merge(t_file **list)
{
	t_opt options;

	initopt(&options);
	if (*list == NULL)
		return ;
	if (!g_options.f)
	{
		if (g_options.r)
		{
			options.r = 1;
			ft_lstmergesort(list, &options);
			ft_lstmergesort(list, &g_options);
		}
		else
		{
			options.r = 0;
			ft_lstmergesort(list, &options);
			ft_lstmergesort(list, &g_options);
		}
	}
}

void		getfiles(t_file *entry, t_file **list, t_max *maxs)
{
	struct dirent	*dptr;
	DIR				*dfd;
	char			*path;
	t_file			*buff;

	if ((dfd = opendir(entry->pathname)) == NULL)
		return ;
	while ((dptr = readdir(dfd)) != NULL)
	{
		path = catpath(entry->pathname, dptr->d_name);
		buff = ft_lstfilenew(path);
		getmaxs(buff, maxs);
		ft_lstfileappend(list, buff);
		free(path);
	}
	closedir(dfd);
	apply_merge(list);
}

int			check_for_a(t_file *current)
{
	if (!g_options.f)
	{
		if (!g_options.a &&
			current->filename[0] == '.' &&
			!g_options.A)
			return (1);
		else if (g_options.A)
		{
			if (ft_strcmp(current->filename, ".") == 0 ||
				ft_strcmp(current->filename, "..") == 0)
				return (1);
		}
	}
	return (0);
}

static void	compute_total(t_file **list, int *result)
{
	t_file		*current;

	current = *list;
	while (current != NULL)
	{
		if (check_for_a(current))
		{
			current = current->next;
			continue ;
		}
		if (current->ferrno)
			return ;
		*result += current->fstat->st_blocks;
		current = current->next;
	}
}

void		printtotal(t_file **list)
{
	int			result;

	result = 0;
	compute_total(list, &result);
	ft_putstr("total ");
	ft_putnbr(result);
	ft_putendl("");
}
