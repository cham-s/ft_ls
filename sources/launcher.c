/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:26:40 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/02 13:54:49 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	ft_list(char *directory, char *options, int ac)
{
    static int i = 0;
	if (ft_strchr(options, 'R'))
		recurdir(directory, options);
	else
    {
        if (ac > 2)
        {
            if (i != 0)
            ft_putchar('\n');
            ft_putstr(directory);
            ft_putendl(":");
        }
        listdir(directory, options);
    }
    i++;
}

void	apply_ft_list(t_file **list, char *options, int ac)
{
	t_file      *tmp;
	struct stat file;

	tmp = NULL;
	if (*list == NULL)
		ft_list(".", options, ac);
	else
	{
		while (*list != NULL)
		{
			tmp = *list;
			if (stat((*list)->filename, &file) < 0)
				ft_perror((*list)->filename);
            else if (S_ISREG(file.st_mode))
                ft_putendl((*list)->filename);
			else
				ft_list((*list)->filename, options, ac);
			*list = (*list)->next;
			free(tmp->filename);
			free(tmp);
		}
	}
	free(options);
}
