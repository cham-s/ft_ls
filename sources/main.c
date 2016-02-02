/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/02 12:35:41 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int		main(int ac, char **av)
{
	t_file	*filelist;
	char	*options;

	if ((options = (char *)ft_memalloc(OPT_MAX)) == NULL)
	{
		exit(EXIT_FAILURE);
	}
	filelist = NULL;
	getoptions(ac, av, options, "Ralrt");
	getdirs(&filelist, ac, av);
	apply_ft_list(&filelist, options);
	return (0);
}
