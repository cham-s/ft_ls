/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/06 15:33:05 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include "libft/includes/libft.h"

int main(int ac, char **av)
{
	t_list	*list;
	char	*dirname;

	dirname = NULL;
	list = NULL;
	if (ac == 1)
		dirname = ".";
	else
		dirname = av[1];
	get_filename(&list, dirname);
	ft_lstprint(list);
}
