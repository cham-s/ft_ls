/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/08 19:12:46 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include "../libft/includes/libft.h"

int main(int ac, char **av)
{
	t_file	*list;
	char	*dirname;

	list = NULL;
	dirname = NULL;
	if (ac == 1)
		dirname = ".";
	else
		dirname = av[1];
	list = get_filename(dirname);
	if (!list)
		ft_putendl("(null)");
	ft_lstprint_dir(&list);
}
