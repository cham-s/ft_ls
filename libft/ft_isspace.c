/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 18:40:33 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/25 18:44:16 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isspace(int c)
{
	unsigned char tc;

	tc = (unsigned char)c;
	if (tc == '\t' || tc == ' ' || tc == '\r'
		|| tc == '\v' || tc == '\f')
		return (true);
	return (false);
}
