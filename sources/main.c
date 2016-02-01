/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/01 18:41:56 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	t_file	*filelist;
	char	*options;

	if ((options = (char *)ft_memalloc(OPT_MAX)) == NULL)
			perror("error from malloc");
	filelist = NULL;
	getoptions(ac, av, options, "Ralrt");
	getdirs(&filelist, ac, av, options);
	apply_ft_list(&filelist, options);
	t_file *tmp;
	tmp = filelist;
	return (0);
}
