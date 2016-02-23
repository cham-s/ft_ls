/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 22:07:14 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/20 18:30:44 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int			cmpsize(t_file *a, t_file *b)
{
	return (a->size >= b->size);
}

int			cmpsize_rev(t_file *a, t_file *b)
{
	return (a->size <= b->size);
}

int			cmpname(t_file *a, t_file *b)
{
	return (ft_strcmp(a->filename, b->filename) <= 0);
}

int			cmpname_rev(t_file *a, t_file *b)
{
	return (ft_strcmp(a->filename, b->filename) >= 0);
}

int			cmptime(t_file *a, t_file *b)
{
	return (a->date >= b->date);
}

int			cmptime_rev(t_file *a, t_file *b)
{
	return (a->date <= b->date);
}
