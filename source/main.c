/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/18 15:52:27 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "../libft/includes/libft.h"

static	void	cleangarbage(t_list **list, char **options)
{
	if (options != NULL)
		ft_strdel(options);
	if (list != NULL)
		ft_lstdelmem(list, ft_memdel);
}

int main(int ac, char **av)
{
	t_list *list;
	list = NULL;
	char *options = ft_getopt(ac, av, "Ralr", &list);
	ft_putendl(options);
	apply_opt(&list);
	cleangarbage(&list, &options);
	return (0);
}
