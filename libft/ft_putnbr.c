/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 19:18:25 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/22 10:49:53 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n)
{
	if (n == -9223372036854775807)
	{
		ft_putstr("-9");
		n = 223372036854775807;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar('0' + n);
	}
}
