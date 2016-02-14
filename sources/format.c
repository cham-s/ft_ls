/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 08:52:13 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/12 16:46:26 by cattouma         ###   ########.fr       */
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

// add to display.c
void    print_path(char *fname)
{
	static int i = 0;

	if (i++ != 0)
		ft_putendl("");
	ft_putstr(fname);
	ft_putendl(":");
}

void    printlinkpath(char *filename)
{
    char    buf[1024];
    size_t  len;

    if ((len = readlink(filename, buf, sizeof(buf) - 1)) != (size_t)-1)
        buf[len] = '\0';
    ft_putstr(" -> ");
    ft_putstr(buf);
}

void    print_device(dev_t device)
{
    ft_putnbr(MAJOR(device));
    ft_putchar(',');
    ft_putstr(" ");
    ft_putnbr(MINOR(device));
    ft_putstr(" ");
}

void    print_size(off_t size, t_max *maxs)
{
    print_space_nbr(maxs->size, size);
}

t_bool  is_device(mode_t mode)
{
    if (S_ISBLK(mode) || S_ISSOCK(mode) ||
            S_ISFIFO(mode) || S_ISCHR(mode))
        return true;
    return false;
}
void    printstat(struct stat *file, char *filename, t_max *maxs, t_bool is_file)
{
	struct passwd   *pwd;
	struct group    *grp;

    grp = NULL;
    perm_format(file);
    ft_putstr("  ");
    print_space_nbr(maxs->lnk, file->st_nlink);
    ft_putstr(" ");
    if ((pwd = getpwuid(file->st_uid)) == NULL)
		print_space_nbr(maxs->uid , file->st_uid);
	else
		print_space_str(maxs->user , pwd->pw_name);
    ft_putstr("  ");
    if ((grp = getgrgid(file->st_gid)) == NULL)
		print_space_nbr(maxs->gid , file->st_gid);
	else
		print_space_str(maxs->group, grp->gr_name);
    ft_putstr("  ");
    if (is_device(file->st_mode))
        print_device(file->st_dev);
    else
    {
        print_size(file->st_size, maxs);
        ft_putstr(" "); // add to the function
    }
    print_ctime(&file->st_mtimespec);
    ft_putstr(" ");
	if (is_file)
		ft_putstr(filename);
	else
		ft_putstr(pathtrim(filename));
    if (S_ISLNK(file->st_mode))
        printlinkpath(filename);
    ft_putendl("");
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

void    print_perm(mode_t mode)
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
}

void	perm_format(struct stat *file)
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
    print_perm(file->st_mode);
}
