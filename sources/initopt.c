/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initopt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 15:15:01 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/27 17:54:26 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	initopt(t_opt *options)
{
	options->g_a = 0;
	options->g_r = 0;
	options->g_s = 0;
	options->a = 0;
	options->d = 0;
	options->f = 0;
	options->l = 0;
	options->p = 0;
	options->r = 0;
	options->t = 0;
}

void	addflag(t_opt *options, char c)
{
	if (c == 'A')
		options->g_a = 1;
	else if (c == 'R')
		options->g_r = 1;
	else if (c == 'S')
		options->g_s = 1;
	else if (c == 'a')
		options->a = 1;
	else if (c == 'd')
		options->d = 1;
	else if (c == 'f')
		options->f = 1;
	else if (c == 'l')
		options->l = 1;
	else if (c == 'p')
		options->p = 1;
	else if (c == 'r')
		options->r = 1;
	else if (c == 't')
		options->t = 1;
}
