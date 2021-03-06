/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:56:20 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/22 09:41:05 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>
#include <time.h>

void	free_content_and_node(t_file *node)
{
	free(node->filename);
	free(node->pathname);
	free(node->fstat);
	free(node);
}

char	*catpath(char *folder, char *file)
{
	size_t	len1;
	size_t	len2;
	char	*name;

	len1 = ft_strlen(folder);
	len2 = ft_strlen(file);
	if ((name = ft_strnew((len1 + len2) + 1)) == NULL)
		return (NULL);
	ft_memcpy(name, folder, len1);
	name[len1] = '/';
	ft_memcpy((name + len1) + 1, file, len2);
	return (name);
}

void	ft_perror(char *name, int errno)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putendl_fd("", 2);
}

int		nbrspace(int max)
{
	int i;

	i = 0;
	while (max)
	{
		i++;
		max /= 10;
	}
	return (i ? i : 1);
}

int		is_dateinrange(time_t atime)
{
	time_t	now;
	long	result;

	result = 0;
	now = time(&now);
	result = atime - now;
	result = (result < 0 ? -result : result);
	return (result <= SIX_MON);
}
