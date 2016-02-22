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

static void	apply_format(t_file **current, char *opts, t_max *maxs)
{
	while (*current != NULL)
	{
		if (check_for_a(*current, opts))
		{
			*current = (*current)->next;
			continue ;
		}
		if (ft_strchr(opts, 'l'))
			print_l_format((*current)->filename, maxs, false);
		else
			printfile(TRIM((*current)->filename), opts);
		*current = (*current)->next;
	}
}

void		listallfiles(t_file **list, char *opts, char *dir, t_max *maxs)
{
	t_file		*current;
	static int	i = 0;

	current = *list;
	if (i++ != 0)
		printdirnl(dir, false);
	if (current && current->next)
	{
		if (ft_strchr(opts, 'l') && current->next->next)
			printtotal(list, opts);
		else if (ft_strchr(opts, 'l') &&
				!current->next->next && OPTIN(opts, 'a'))
			printtotal(list, opts);
	}
	apply_format(&current, opts, maxs);
}
