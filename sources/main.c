/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/20 16:47:54 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "../libft/includes/libft.h"

static	void	cleangarbage(t_list **list, char **options)
{
	if (options != NULL)
		ft_strdel(options);
	if (list != NULL)
		ft_lstdelmem(list, ft_strdel);
}

int main(int ac, char **av)
{
	t_list *filelist;
	filelist = NULL;
	char *options = ft_getopt(ac, av, "Ralrt", &filelist);
	apply_opt(&filelist);
	cleangarbage(&filelist, &options);
	return (0);
}
