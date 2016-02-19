/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 14:31:36 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/19 19:37:33 by cattouma         ###   ########.fr       */
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

void	apply_merge(t_file **list, char *options)
{
	if (*list == NULL)
		return ;
	if (ft_strchr(options, 'r'))
		if (ft_strchr(options, 't'))
		{
			ft_lstmergesort(list, "r");
			ft_lstmergesort(list, "tr");
		}
		else
			ft_lstmergesort(list, "r");
	else
	{
		if (ft_strchr(options, 't'))
		{
			ft_lstmergesort(list, "");
			ft_lstmergesort(list, "t");
		}
		else
			ft_lstmergesort(list, "");
	}
}

void	getfiles(char *filename, t_file **list, char *options, t_max *maxs)
{
	struct dirent	*dptr;
	DIR				*dfd;
	char			*path;

	if ((dfd = opendir(filename)) == NULL)
	{
		ft_perror(filename);
		return ;
	}
	while ((dptr = readdir(dfd)) != NULL)
	{
		path = catpath(filename, dptr->d_name);
		getmaxs(path, maxs, options);
		ft_lstfileappend(list, ft_lstfilenew(path));
		free(path);
	}
	closedir(dfd);
	apply_merge(list, options);
}

int		check_for_a(t_file *current, char *options)
{
	if (OPTIN(options, 'a') == NULL &&
		TRIM(current->filename)[0] == '.' &&
		OPTIN(options, 'A') == NULL)
		return (1);
	else if (OPTIN(options, 'A') && OPTIN(options, 'a') == NULL)
	{
		if (TRIM(current->filename) == "." ||
			TRIM(current->filename) == "..")
			return (1);
	}
	return (0);
}

void	compute_total(t_file **list, int *result,
		struct stat *file, char *options)
{
	t_file		*current;

	current = *list;
	while (current != NULL)
	{
		if (check_for_a(current, options))
		{
			current = current->next;
			continue ;
		}
		if (lstat(current->filename, file) < 0)
			return ;
		if (S_ISLNK(file->st_mode))
			*result += file->st_blocks;
		else
		{
			if (stat(current->filename, file) < 0)
				return ;
			*result += file->st_blocks;
		}
		current = current->next;
	}
}

void	printtotal(t_file **list, char *options)
{
	int			result;
	struct stat	file;

	result = 0;
	compute_total(list, &result, &file, options);
	ft_putstr("total ");
	ft_putnbr(result);
	ft_putendl("");
}

void	printdirnl(char *directory, t_bool first)
{
	if (first)
	{
		ft_putstr(directory);
		ft_putendl(":");
	}
	else
	{
		ft_putchar('\n');
		ft_putstr(directory);
		ft_putendl(":");
	}
}

void	apply_format(t_file **current, char *options, t_max *maxs)
{
	while (*current != NULL)
	{
		if (check_for_a(*current, options))
		{
			*current = (*current)->next;
			continue ;
		}
		if (ft_strchr(options, 'l'))
			print_l_format((*current)->filename, maxs, false);
		else
			printfile(TRIM((*current)->filename), options);
		*current = (*current)->next;
	}
}

void	listallfiles(t_file **list, char *options, char *directory, t_max *maxs)
{
	t_file		*current;
	static int	i = 0;

	current = *list;
	if (i++ != 0)
		printdirnl(directory, false);
	if (current && current->next)
	{
		if (ft_strchr(options, 'l') && current->next->next)
			printtotal(list, options);
		else if (ft_strchr(options, 'l') &&
				!current->next->next && OPTIN(options, 'a'))
			printtotal(list, options);
	}
	apply_format(&current, options, maxs);
}
