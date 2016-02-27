/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 14:39:15 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/27 14:58:54 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int			cmptime_rev(t_file *a, t_file *b)
{
	return (a->fstat->st_mtimespec.tv_sec <= b->fstat->st_mtimespec.tv_sec);
}
