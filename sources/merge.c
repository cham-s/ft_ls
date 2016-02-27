/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 22:07:14 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/27 14:45:32 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int			cmpsize(t_file *a, t_file *b)
{
	return (a->fstat->st_size >= b->fstat->st_size);
}

int			cmpsize_rev(t_file *a, t_file *b)
{
	return (a->fstat->st_size <= b->fstat->st_size);
}

int			cmpname(t_file *a, t_file *b)
{
	return (ft_strcmp(a->pathname, b->pathname) <= 0);
}

int			cmpname_rev(t_file *a, t_file *b)
{
	return (ft_strcmp(a->pathname, b->pathname) >= 0);
}

int			cmptime(t_file *a, t_file *b)
{
	return (a->fstat->st_mtimespec.tv_sec >= b->fstat->st_mtimespec.tv_sec);
}
