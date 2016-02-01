/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:26:40 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/01 17:26:22 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void	ft_list(char *directory, char *options)
{
	if (ft_strchr(options, 'R'))
		recurdir(directory, options);
	else
		listdir(directory, options);
}

void	apply_ft_list(t_file **list, char *options)
{
	t_file *tmp;
	struct stat file;

	tmp = NULL;
	if (*list == NULL)
		ft_list(".", options);
	else
	{
		while (*list != NULL)
		{
			tmp = *list;
			if (stat((*list)->filename, &file) < 0)
				ft_perror((*list)->filename);
			else
				ft_list((*list)->filename, options);
			*list = (*list)->next;
			free(tmp->filename);
			free(tmp);
		}
	}
	free(options);
}
