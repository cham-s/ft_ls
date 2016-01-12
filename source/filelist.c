/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:36:42 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/09 22:30:53 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/libls.h"
#include <sys/stat.h>

t_file	*ft_lstfilenew(const char *content, t_bool is_dir)
{
	t_file	*fresh;
	size_t	len;

	fresh = (t_file *)malloc(sizeof(t_file));
	if (!fresh)
		return (NULL);
	if (!content)
		fresh->filename = NULL;
	else
	{
		len = ft_strlen(content);
		fresh->filename = ft_strnew(len);
		ft_memcpy(fresh->filename, content, len);
	}
	fresh->next = NULL;
	fresh->is_dir = is_dir;
	return (fresh);
}

t_file	*ft_lstfileappend(t_file **alst, t_file *new)
{
	t_file *current;

	current = *alst;
	if (!current)
	{
		*alst = new;
		return(*alst);
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
		current = current->next;
		return (current);
	}
}

void	ft_lstfileprint(t_file **alst)
{
	t_file *current;

	current = *alst;
	if (!current)
		return ;
	while (current)
	{
        ft_putendl(current->filename);
		current = current->next;
	}
}

void	ft_lstfileprint_l_format(t_file **alst)
{
	t_file *current;

	current = *alst;
	if (!current)
		return ;
	while (current)
	{
		print_l_format(current->filename);
		current = current->next;
	}
}
