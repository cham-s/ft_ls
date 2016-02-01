/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/01 16:19:36 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	t_file *filelist;
	char *options;

	if ((options = (char *)ft_memalloc(OPT_MAX)) == NULL)
			perror("error from malloc");
	filelist = NULL;
	getoptions(ac, av, options, "Ralrt");
	getdirs(&filelist, ac, av);
	//apply_ft_list(filelist, options);
	ft_putendl(options);

	t_file *tmp;
	tmp = filelist;
	while (filelist != NULL)
	{
		tmp =  filelist;
		ft_putendl(filelist->filename);
		filelist = filelist->next;
		free(tmp->filename);
		free(tmp);
	}
	free(options);
	while
	return (0);
}
