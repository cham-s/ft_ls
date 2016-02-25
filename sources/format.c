/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 21:23:46 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/24 14:45:04 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <stdio.h>
#include <time.h>
#include <sys/xattr.h>
#include <sys/acl.h>

void	printlinkpath(char *filename)
{
	char	buf[1024];
	size_t	len;

	if ((len = readlink(filename, buf, sizeof(buf) - 1)) != (size_t)-1)
		buf[len] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buf);
}

void	print_device(dev_t device, t_max *maxs)
{
	print_space_nbr(maxs->major, major(device));
	ft_putchar(',');
	ft_putstr(" ");
	print_space_nbr(maxs->minor, minor(device));
	ft_putstr(" ");
}

void	print_size(off_t size, t_max *maxs)
{
	print_space_nbr(maxs->size, size);
}

t_bool	is_device(mode_t mode)
{
	if (S_ISBLK(mode) || S_ISCHR(mode))
		return (true);
	return (false);
}

void	printstat2(t_file *entry, t_bool is_file)
{
	print_ctime(&entry->fstat->st_mtimespec);
	ft_putstr(" ");
	if (is_file)
		ft_putstr(entry->filename);
	else
		ft_putstr(entry->filename);
	if (S_ISLNK(entry->fstat->st_mode))
		printlinkpath(entry->pathname);
	if (g_options.p)
		if (S_ISDIR(entry->fstat->st_mode))
			ft_putchar('/');
	ft_putendl("");
}
