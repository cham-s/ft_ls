/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/06 15:33:05 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "includes/libft.h" 
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <stdio.h>

static void	perm_format(struct stat *file)
{
	ft_putchar(S_ISDIR(file->st_mode) ? 'd' : '-');
	ft_putchar((file->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((file->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((file->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXOTH) ? 'x' : '-');
}

static void	print_l_format(char *filename)
{
	struct stat file; 
	struct passwd *pwd;
	struct group *grp = NULL;

	if (stat(filename, &file) < 0)
		return ; // TODO: handle error withou perror 
	if ((pwd = getpwuid(file.st_uid)) && (grp = getgrgid(file.st_gid)) == NULL)
		return ; // TODO: handle error withou perror
	perm_format(&file);
	ft_putstr("  ");
	ft_putnbr(file.st_nlink);
	ft_putstr("  ");
	ft_putstr(pwd->pw_name);
	ft_putstr("  ");
	ft_putstr(grp->gr_name);
	ft_putstr("  ");
	ft_putnbr(file.st_size);
	ft_putstr("  ");
	ft_putendl("");
}

int main(int ac, char **av)
{
	struct dirent *entry;
	DIR *dfd;
	char *dirname;

	if (ac == 1)
		dirname = ".";
	else
		dirname = av[1];
	if ((dfd = opendir(dirname)) == NULL)
		perror("ft_ls: no such file or directory");
	while ((entry = readdir(dfd)) != NULL)
		print_l_format(entry->d_name);
}