/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 19:18:15 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/03 20:31:12 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int spc = nbrs - nbrspace(size);
	while (spc--)
		ft_putchar(' ');
	ft_putnbr(size);
}
