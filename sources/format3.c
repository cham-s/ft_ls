/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 21:58:55 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/19 22:29:40 by cattouma         ###   ########.fr       */
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

void	printstat(struct stat *file, char *name, t_max *maxs, t_bool is_file)
{
	struct passwd	*pwd;
	struct group	*grp;

	grp = NULL;
	perm_format(file, name);
	print_space_nbr(maxs->lnk, file->st_nlink);
	ft_putstr(" ");
	if ((pwd = getpwuid(file->st_uid)) == NULL)
		print_space_nbr(maxs->uid, file->st_uid);
	else
		print_space_str(maxs->user, pwd->pw_name);
	ft_putstr("  ");
	if ((grp = getgrgid(file->st_gid)) == NULL)
		print_space_nbr(maxs->gid, file->st_gid);
	else
		print_space_str(maxs->group, grp->gr_name);
	ft_putstr("  ");
	if (is_device(file->st_mode))
		print_device(file->st_rdev, maxs);
	else
	{
		print_size(file->st_size, maxs);
		ft_putstr(" ");
	}
	printstat2(file, name, is_file);
}

void	print_l_format(char *filename, t_max *maxs, t_bool is_file)
{
	struct stat file;

	if (lstat(filename, &file) < 0)
		return ;
	if (S_ISLNK(file.st_mode))
		printstat(&file, filename, maxs, is_file);
	else
	{
		if (stat(filename, &file) < 0)
			return ;
		printstat(&file, filename, maxs, is_file);
	}
}

void	has_xattr_or_acl(char *path)
{
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_putchar('@');
	else if (acl_get_file(path, ACL_TYPE_EXTENDED))
		ft_putchar('+');
	else
		ft_putchar(' ');
	ft_putchar(' ');
}

void	print_perm(mode_t mode, char *path)
{
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	if (mode & S_ISUID)
		ft_putchar((mode & S_IXUSR) ? 's' : 'S');
	else
		ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	if (mode & S_ISGID)
		ft_putchar((mode & S_IXGRP) ? 's' : 'S');
	else
		ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	if (mode & S_ISVTX)
		ft_putchar((mode & S_IXOTH) ? 't' : 'T');
	else
		ft_putchar((mode & S_IXOTH) ? 'x' : '-');
	has_xattr_or_acl(path);
}

void	perm_format(struct stat *file, char *path)
{
	if (S_ISDIR(file->st_mode))
		ft_putchar('d');
	else if (S_ISBLK(file->st_mode))
		ft_putchar('b');
	else if (S_ISCHR(file->st_mode))
		ft_putchar('c');
	else if (S_ISLNK(file->st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(file->st_mode))
		ft_putchar('s');
	else if (S_ISFIFO(file->st_mode))
		ft_putchar('p');
	else
		ft_putchar('-');
	print_perm(file->st_mode, path);
}
