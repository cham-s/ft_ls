/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:26:40 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/29 17:52:10 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	ft_list(char *filename, char *options)
{
	filename++;
	options++;
	return ;
}

void	apply_ft_list(t_file **list, char *options)
{
	t_file *tmp;

	tmp = NULL;
	if (*list == NULL)
		ft_list(".", options);
	else
	{
		while (*list != NULL)
		{
			tmp = *list;
			ft_list((*list)->filename, options);
			*list = (*list)->next;
			free(tmp->filename);
			free(tmp);
		}
	}
	free(options);
}
