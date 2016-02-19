/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 format.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: cattouma <cattouma@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2016/02/17 13:44:25 by cattouma		   #+#	  #+#			  */
/*	 Updated: 2016/02/17 13:47:54 by cattouma		  ###	########.fr		  */
/*																			  */
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

void	printstat2(struct stat *file, char *filename, t_bool is_file)
{
	print_ctime(&file->st_mtimespec);
	ft_putstr(" ");
	if (is_file)
		ft_putstr(filename);
	else
		ft_putstr(TRIM(filename));
	if (S_ISLNK(file->st_mode))
		printlinkpath(filename);
	ft_putendl("");
}
