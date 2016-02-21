/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 utility.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: cattouma <cattouma@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2016/02/17 14:05:06 by cattouma		   #+#	  #+#			  */
/*	 Updated: 2016/02/17 19:07:14 by cattouma		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>
#include <time.h>

void	free_content_and_node(t_file *node)
{
	free(node->filename);
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

void	ft_perror(char *name)
{
	char *merror;

	merror = ft_strjoin("ft_ls: ", name);
	perror(merror);
	free(merror);
}

int				nbrspace(int max)
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

