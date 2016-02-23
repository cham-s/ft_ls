/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:58:35 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/22 09:00:07 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	browse_list_for_maxs(t_file **list, t_max *maxs)
{
	t_file		*current;

	current = *list;
	while (current != NULL)
	{
		getmaxs(current->filename, maxs);
		current = current->next;
	}
}

void	check_fts_open(char *s)
{
	if (ft_strcmp(s, "") == 0)
	{
		ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
}

void	printfile(char *fname)
{
	if (!g_options.l)
		ft_putendl(fname);
}

void	print_space_nbr(int max, long long size)
{
	int spc;

	spc = max - nbrspace(size);
	while (spc--)
		ft_putchar(' ');
	ft_putnbr(size);
}

void	print_space_str(int max, char *str)
{
	int spc;

	spc = max - (int)ft_strlen(str);
	ft_putstr(str);
	while (spc--)
		ft_putchar(' ');
}
