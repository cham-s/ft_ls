/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 15:59:04 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/02 13:53:59 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void    usage(char c)
{
    ft_putstr_fd("ft_ls: illegal option -- ", 2);
    ft_putchar_fd(c, 2);
    ft_putendl_fd("\nusage: ft_ls [-Ralrt] [file ...]", 2);
    exit (EXIT_FAILURE);
}

void            attachlist(t_file **a, t_file **b)
{
    t_file *tmp;

    tmp = NULL;
	if (*a != NULL)
	{
		tmp  = *a;
		while ((*a)->next != NULL)
			*a = (*a)->next;
		(*a)->next = *b;
		*b = tmp;
	}
}

void			getdirs(t_file **list, int ac, char **av)
{
	t_file		*errors;
    t_file      *filelist;
	struct stat	file;

    filelist = NULL;
	errors = NULL;
	av++;
    while (ac-- > 1 && (*av)[0] == '-' && (*av)[1] != '\0')
		av++;
    while (ac-- >= 1)
    {
		if (stat(*av, &file) < 0)
			ft_lstfileappend(&errors, ft_lstfilenew(*av));
		else
        {
            if (!S_ISDIR(file.st_mode))
                ft_lstfileappend(&filelist, ft_lstfilenew(*av));
            else
                ft_lstfileappend(list, ft_lstfilenew(*av));
        }
        av++;
    }
	ft_lstmergesort(&errors, "");
	ft_lstmergesort(&filelist, "");
	ft_lstmergesort(list, "");
    attachlist(&errors, &filelist);
    attachlist(&filelist, list);
}

void			getoptions(int ac, char **av, char *options, char* optlist)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = options;
	i++;
    while (ac-- > 1 && av[i][0] == '-' && av[i][1] != '\0')
	{
		j = 1;
		while (av[i][j])
		{
			if (ft_strchr(optlist, av[i][j]) == NULL)
				usage(av[i][j]);
			else
			{
				if (ft_strchr(tmp, av[i][j]) == NULL)
				{
					while(*options)
						options++;
					*options = av[i][j];
				}
			}
			j++;
		}
		i++;
	}
}
