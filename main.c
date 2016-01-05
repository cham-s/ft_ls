/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/05 15:50:21 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "includes/libft.h" 
#include <stdlib.h>
#include <sys/stat.h>

static void	perm_format(struct stat *file)
{
	char res;
	ft_putchar(S_ISDIR(file->st_mode) ? 'd' : '-');
	ft_putchar((file->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((file->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((file->st_mode & S_IWOTH) ? 'r' : '-');
	ft_putchar((file->st_mode & S_IXOTH) ? 'w' : '-');
	ft_putchar((file->st_mode & S_IXOTH) ? 'x' : '-');
}

static void	print_l_format(char *filename)
{
	struct stat file; 

	if (stat(filename, &file) < 0)
		return ;

}

int main()
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			ft_putendl(ent->d_name);
		}
		closedir(dir);
	}
	else
	{
		ft_putendl("error");
	}

	char *filename = "main.c";
	struct stat *tmpstat;

	tmpstat = malloc(sizeof(struct stat));
	stat(filename, tmpstat);
	int size = tmpstat->st_size;
	ft_putnbr(size);
	ft_putendl("");
	free(tmpstat);
}