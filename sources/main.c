/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 22:06:28 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/19 22:34:09 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

t_opt	g_options;

int		main(int ac, char **av)
{
	t_file	**tablist;
	char	*options;
	int		len;

	initopt(&g_options);
	if ((options = (char *)ft_memalloc(OPT_SIZE)) == NULL)
		return (EXIT_FAILURE);
	if ((tablist = (t_file **)malloc(sizeof(t_file *) * LIST_SIZE)) == NULL)
		return (EXIT_FAILURE);
	tablist[ERRORS] = NULL;
	tablist[FILES] = NULL;
	tablist[DIRS] = NULL;
	getoptions(ac, av, options, OPTS);
	getdirs(tablist, ac, av);
	apply_ft_list(tablist);
	return (0);
	free(options);
	len = LIST_SIZE;
	while (len--)
		free(*tablist);
	free(tablist);
}
