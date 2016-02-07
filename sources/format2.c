/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 19:18:15 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/07 11:24:27 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int		nbrspace(int max)
{
	int i;

	i = 0;
	while (max)
	{
		i++;
		max /= 10;
	}
	return (i);
}

void	printwithspace(int nbrs, int size)
{
	int spc;
	spc = nbrs - nbrspace(size);
	spc = (spc < 0? 0: spc);
	while (spc--)
		ft_putchar(' ');
	ft_putnbr(size);
}
