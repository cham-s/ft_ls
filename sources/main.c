/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: cattouma <cattouma@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2016/01/04 14:54:05 by cattouma		   #+#	  #+#			  */
/*	 Updated: 2016/02/17 13:47:55 by cattouma		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int		main(int ac, char **av)
{
	t_file	**tablist;
	char	*options;

	if ((options = (char *)ft_memalloc(OPT_SIZE)) == NULL)
		return (EXIT_FAILURE);
	if ((tablist = (t_file **)malloc(sizeof(t_file *) * LIST_SIZE)) == NULL)
		return (EXIT_FAILURE);
	tablist[ERRORS] = NULL;
	tablist[FILES] = NULL;
	tablist[DIRS] = NULL;
	getoptions(ac, av, options, OPTS);
	getdirs(tablist, ac, av, options);
	apply_ft_list(tablist, options, ac, av);
	return (0);
}
