	/*while (filelist != NULL)
	{
		tmp =  filelist;
		ft_putendl(filelist->filename);
		filelist = filelist->next;
		free(tmp->filename);
		free(tmp);
	}
	free(options);*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 15:59:04 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/01 17:54:02 by cattouma         ###   ########.fr       */
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

void			getdirs(t_file **list, int ac, char **av, char *options)
{
	av++;
    while (ac-- > 1 && (*av)[0] == '-')
		av++;
    while (ac-- >= 1)
    {
        ft_lstfileappend(list, ft_lstfilenew(*av));
        av++;
    }
	ft_lstmergesort(list, options);
}

void			getoptions(int ac, char **av, char *options, char* optlist)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = options;
	i++;
    while (ac-- > 1 && av[i][0] == '-')
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
