/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:30:48 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/22 08:32:43 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void		printdirnl(char *dir, t_bool first)
{
	if (first)
	{
		ft_putstr(dir);
		ft_putendl(":");
	}
	else
	{
		ft_putchar('\n');
		ft_putstr(dir);
		ft_putendl(":");
	}
}

static void	apply_format(t_file **current, t_max *maxs)
{
	while (*current != NULL)
	{
		if (check_for_a(*current))
		{
			*current = (*current)->next;
			continue ;
		}
		if (g_options.l)
			print_l_format(*current, maxs, false);
		else
			printfile(*current);
		*current = (*current)->next;
	}
}

void		listallfiles(t_file **list, t_file *entry, t_max *maxs)
{
	t_file		*current;
	static int	i = 0;

	current = *list;
	if (i++ != 0 && S_ISDIR(entry->fstat->st_mode))
		printdirnl(entry->pathname, false);
	if (entry->ferrno)
		ft_perror(entry->filename ,entry->ferrno);
	if (current && current->next)
	{
		if (g_options.l && current->next->next)
			printtotal(list);
		else if (g_options.l &&
				!current->next->next && g_options.a)
			printtotal(list);
	}
	apply_format(&current, maxs);
}
