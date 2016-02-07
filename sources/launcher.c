/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:26:40 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/07 09:41:35 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void    nlafterfile(t_file *entry)
{
	struct stat file;

    if (entry->next != NULL)
    {
        if (stat(entry->next->filename, &file) < 0)
            return ;
        if (S_ISDIR(file.st_mode))
            ft_putchar('\n');
    }
}

void	ft_list(char *directory, char *options, int ac, char **av)
{
    static int i = 0;

	// a virer?
    av++;
    ac++;
	if (ft_strchr(options, 'R'))
		recurdir(directory, options);
	else
        listdir(directory, options);
    i++;
}

static void		checkfile(t_file *list, int (*fstat)(const char *name, struct stat *buf))
{

	struct stat file;

	if (fstat((list)->filename, &file) < 0)
	{
		ft_perror((list)->filename);
		if ((list)->next)
		{
			stat((list)->next->filename, &file);
			if (S_ISDIR(file.st_mode))
				printdirnl((list)->next->filename, true);
		}
	}
	else if (!S_ISDIR(file.st_mode))
	{
		ft_putendl((list)->filename);
		nlafterfile(list);
	}
}

void	apply_ft_list(t_file **list, char *options, int ac, char **av)
{
	t_file      *tmp;
	struct stat file;
    static int  i = 0;

	tmp = NULL;
	if (*list == NULL)
		ft_list(".", options, ac, av);
	else
	{
		while (*list != NULL)
		{
			tmp = *list;
			if (stat((*list)->filename, &file) < 0)
				checkfile(*list, lstat);
			else if (S_ISREG(file.st_mode))
				checkfile(*list, stat);
			else
            {
                if ((*list)->next != NULL && i == 0)
                    printdirnl((*list)->filename, true);
                else if (i != 0 && ft_strchr(options, 'R') == NULL)
                    printdirnl((*list)->filename, false);
				ft_list((*list)->filename, options, ac, av);
                i++;
            }
			*list = (*list)->next;
			free(tmp->filename);
			free(tmp);
		}
	}
	free(options);
}
