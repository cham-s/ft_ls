/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 22:13:19 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/27 18:02:51 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void		usage(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: ft_ls [-ARSadflprt] [file ...]", 2);
	exit(EXIT_FAILURE);
}

void			check_file(t_file **tablist, char **av, char *name)
{
	struct stat	file;

	if ((lstat(name, &file)) < 0)
		ft_lstfileappend(&tablist[ERRORS], ft_lstfilenew(*av));
	if (S_ISLNK(file.st_mode) && g_options.l)
		ft_lstfileappend(&tablist[FILES], ft_lstfilenew(*av));
	else if ((stat(name, &file)) == 0)
	{
		if (g_options.d)
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

void			getdirs(t_file **tablist, int ac, char **av)
{
	t_opt opts;

	initopt(&opts);
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
		check_file(tablist, av, *av);
		av++;
	}
	ft_lstmergesort(&tablist[ERRORS], &opts);
	apply_merge(&tablist[FILES]);
	apply_merge(&tablist[DIRS]);
	if (tablist[ERRORS] == NULL && tablist[FILES] == NULL
			&& tablist[DIRS] == NULL && g_options.d)
		ft_lstfileappend(&tablist[FILES], ft_lstfilenew("."));
}

static void		addopt(char *opts, char c)
{
	addflag(&g_options, c);
	while (*opts)
		opts++;
	*opts = c;
}

void			getoptions(int ac, char **av, char *opts, char *optlist)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = opts;
	i++;
	while (ac-- > 1 && av[i][0] == '-' && av[i][1] != '\0')
	{
		j = 1;
		if (ft_strcmp(av[i], "--") == 0)
			break ;
		while (av[i][j])
		{
			if (OPTIN(optlist, av[i][j]) == NULL)
				usage(av[i][j]);
			else
			{
				if (OPTIN(tmp, av[i][j]) == NULL)
					addopt(opts, av[i][j]);
			}
			j++;
		}
		i++;
	}
}
