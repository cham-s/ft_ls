/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:26:40 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/03 17:53:56 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	        ft_list(char *directory, char *options, int ac, char **av)
{
    static int i = 0;

    if (ac > 1)
    {
        if (i == 0 && ((av[1][0] == '-' && ac > 3) || (ac > 2 && av[1][0] != '-')))
        {
            ft_putstr(directory);
            ft_putendl(":");
        }
    }
	if (ft_strchr(options, 'R'))
		recurdir(directory, options);
	else
        listdir(directory, options);
    i++;
}

/*static void     spaceafterfile(t_file **entry)
{
	struct stat file;
    if (stat((*entry)->next->filename, &file) < 0)
        ft_perror((*entry)->next->filename);
    if (S_ISDIR(file.st_mode))
        ft_putchar('\n');
}*/

void            apply_ft_list(t_file **list, char *options, int ac, char **av)
{
	t_file      *tmp;

	tmp = NULL;
	if (*list == NULL)
		ft_list(".", options, ac, av);
	else
	{
		while (*list != NULL)
		{
			tmp = *list;
			ft_list((*list)->filename, options, ac, av);
			*list = (*list)->next;
			free(tmp->filename);
			free(tmp);
		}
	}
	free(options);
}
