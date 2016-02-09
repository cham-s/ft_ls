/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 19:18:15 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/09 15:25:50 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <time.h>

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

void			printwithspace(int nbrs, int size)
{
	int spc;
	spc = nbrs - nbrspace(size);
	while (spc--)
		ft_putchar(' ');
	ft_putnbr(size);
}

static int		is_dateinrange(time_t atime)
{
	time_t	now;
	long	result;

	result = 0;
	now = time(&now);
	result = atime - now;
	result *= 1;
	return (result <= SIX_MON);
}

void			print_ctime(struct timespec *atime)
{
	char *strtime; 
	char *end;
	char *hours;
	char *year;

	strtime = ctime(&(atime)->tv_sec);
	year = ft_strrchr(strtime, ' ') + 1;
	strtime = ft_strchr(strtime, ' ') + 1;
	end = ft_strrchr(strtime, ':');
	*end = '\0';
	end = ft_strrchr(strtime, ' ');
	*end = '\0';
	end = ft_strrchr(year, '\n');
	*end = '\0';
	hours = end + 1;
	ft_putstr(strtime);
	ft_putstr(" ");
	if (is_dateinrange(atime->tv_sec))
		ft_putstr(year);
	else
		ft_putstr(hours);
}
