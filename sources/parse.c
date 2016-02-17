/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: cattouma <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2016/01/29 15:59:04 by cattouma		   #+#	  #+#			  */
/*	 Updated: 2016/02/17 13:17:25 by cattouma		  ###	########.fr		  */
/*																			  */
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

void			attachlist(t_file **a, t_file **b)
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
void			check_file(t_file **tablist, char **av, char *filename, char *options)
{
	struct stat	file;

	if ((lstat(filename, &file)) < 0)
		ft_lstfileappend(&tablist[ERRORS], ft_lstfilenew(*av));
	if (S_ISLNK(file.st_mode) && isoptin(options, 'l'))
			ft_lstfileappend(&tablist[FILES], ft_lstfilenew(*av));
	else if ((stat(filename, &file)) == 0) 
	{
		if (isoptin(options, 'd'))
				ft_lstfileappend(&tablist[FILES], ft_lstfilenew(*av));
		else
		{
			if (S_ISREG(file.st_mode))
				ft_lstfileappend(&tablist[FILES], ft_lstfilenew(*av));
			else
				ft_lstfileappend(&tablist[DIRS], ft_lstfilenew(*av));
		}
	}
}
void			getdirs(t_file **tablist, int ac, char **av, char *options)
{
	av++;
	while (ac-- > 1 && (*av)[0] == '-' && (*av)[1] != '\0')
	{
		if (ft_strcmp(*av, "--") == 0)
		{
			ac--;
			av++;
			break ;
		}
		av++;
	}
	while (ac-- >= 1)
	{
		if (ft_strcmp(*av, "") == 0)
		{
			ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
			exit(EXIT_FAILURE);
		}
		check_file(tablist, av, *av, options);
		av++;
	}
	apply_merge(&tablist[ERRORS], "");
	apply_merge(&tablist[FILES], options);
	apply_merge(&tablist[DIRS], options);
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
		if (ft_strcmp(av[i], "--") == 0)
			break ;
		while (av[i][j])
		{
			if (isoptin(optlist, av[i][j]) == NULL)
				usage(av[i][j]);
			else
			{
				if (isoptin(tmp, av[i][j]) == NULL)
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
