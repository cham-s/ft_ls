/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 22:02:26 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/27 17:51:57 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>

void	ft_list(t_file *entry)
{
	static int i = 0;

	if (g_options.g_r)
		recurdir(entry);
	else
		listdir(entry);
	i++;
}

void	print_errors(t_file **list)
{
	t_file		*tmp;
	t_bool		is_empty;

	is_empty = (list[ERRORS] == NULL ? true : false);
	while (list[ERRORS] != NULL)
	{
		tmp = list[ERRORS];
		if (list[ERRORS]->ferrno)
			ft_perror(list[ERRORS]->pathname, list[ERRORS]->ferrno);
		list[ERRORS] = list[ERRORS]->next;
		free_content_and_node(tmp);
	}
	if (list[DIRS])
		if (list[DIRS]->next == NULL && is_empty == false)
			printdirnl(list[DIRS]->pathname, true);
}

void	print_files(t_file **list, t_max *maxs)
{
	t_file *tmp;
	t_bool is_empty;

	is_empty = (list[FILES] == NULL ? true : false);
	while (list[FILES] != NULL)
	{
		list[FILES]->from_file = true;
		tmp = list[FILES];
		if (g_options.l)
			print_l_format((list[FILES]), maxs);
		else
			ft_putendl((list[FILES])->pathname);
		list[FILES] = list[FILES]->next;
		free_content_and_node(tmp);
	}
	if (list[DIRS] != NULL && is_empty == false)
		ft_putchar('\n');
	if (list[DIRS])
		if (list[DIRS]->next == NULL && is_empty == false)
			printdirnl(list[DIRS]->pathname, true);
}

void	print_folders(t_file **list)
{
	t_file		*tmp;
	static int	i = 0;

	if (list[DIRS])
	{
		if (i == 0 && (list[DIRS]->next != NULL ||
		(!list[FILES] && list[ERRORS])))
			printdirnl(list[DIRS]->pathname, true);
	}
	while (list[DIRS] != NULL)
	{
		tmp = list[DIRS];
		ft_list(list[DIRS]);
		list[DIRS] = list[DIRS]->next;
		free_content_and_node(tmp);
	}
	i++;
}

void	apply_ft_list(t_file **tablist)
{
	t_max	maxs;

	if (tablist[ERRORS] == NULL && tablist[FILES] == NULL
			&& tablist[DIRS] == NULL)
		ft_list(ft_lstfilenew("."));
	else
	{
		initmax(&maxs);
		browse_list_for_maxs(&tablist[FILES], &maxs);
		print_errors(tablist);
		print_files(tablist, &maxs);
		print_folders(tablist);
	}
}
