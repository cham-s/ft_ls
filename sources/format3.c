/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 21:58:55 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/26 17:42:47 by cattouma         ###   ########.fr       */
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

void	printstat(t_file *entry, t_max *maxs)
{
	struct passwd	*pwd;
	struct group	*grp;

	grp = NULL;
	perm_format(entry);
	print_space_nbr(maxs->lnk, entry->fstat->st_nlink);
	ft_putstr(" ");
	if ((pwd = getpwuid(entry->fstat->st_uid)) == NULL)
		print_space_nbr(maxs->uid, entry->fstat->st_uid);
	else
		print_space_str(maxs->user, pwd->pw_name);
	ft_putstr("  ");
	if ((grp = getgrgid(entry->fstat->st_gid)) == NULL)
		print_space_nbr(maxs->gid, entry->fstat->st_gid);
	else
		print_space_str(maxs->group, grp->gr_name);
	ft_putstr("  ");
	if (is_device(entry->fstat->st_mode))
		print_device(entry->fstat->st_rdev, maxs);
	else
	{
		print_size(entry->fstat->st_size, maxs);
		ft_putstr(" ");
	}
	printstat2(entry);
}

void	print_l_format(t_file *entry, t_max *maxs)
{
	if (entry->ferrno)
		return ;
	printstat(entry , maxs);
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

void	print_perm(t_file *entry)
{
	ft_putchar((entry->fstat->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((entry->fstat->st_mode & S_IWUSR) ? 'w' : '-');
	if (entry->fstat->st_mode & S_ISUID)
		ft_putchar((entry->fstat->st_mode & S_IXUSR) ? 's' : 'S');
	else
		ft_putchar((entry->fstat->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((entry->fstat->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((entry->fstat->st_mode & S_IWGRP) ? 'w' : '-');
	if (entry->fstat->st_mode & S_ISGID)
		ft_putchar((entry->fstat->st_mode & S_IXGRP) ? 's' : 'S');
	else
		ft_putchar((entry->fstat->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((entry->fstat->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((entry->fstat->st_mode & S_IWOTH) ? 'w' : '-');
	if (entry->fstat->st_mode & S_ISVTX)
		ft_putchar((entry->fstat->st_mode & S_IXOTH) ? 't' : 'T');
	else
		ft_putchar((entry->fstat->st_mode & S_IXOTH) ? 'x' : '-');
	has_xattr_or_acl(entry->pathname);
}

void	perm_format(t_file *entry)
{
	if (S_ISDIR(entry->fstat->st_mode))
		ft_putchar('d');
	else if (S_ISBLK(entry->fstat->st_mode))
		ft_putchar('b');
	else if (S_ISCHR(entry->fstat->st_mode))
		ft_putchar('c');
	else if (S_ISLNK(entry->fstat->st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(entry->fstat->st_mode))
		ft_putchar('s');
	else if (S_ISFIFO(entry->fstat->st_mode))
		ft_putchar('p');
	else
		ft_putchar('-');
	print_perm(entry);
}
