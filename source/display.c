#include "libls.h"
#include "../libft/includes/libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <stdio.h>

t_file	*get_filename(char *dirname)
{
	t_file	*list;
	list = NULL;
	struct dirent *entry;
	DIR *dfd;

	if ((dfd = opendir(dirname)) == NULL)
	{
		return (NULL);
	}
	while ((entry = readdir(dfd)) != NULL)
		ft_lstfileappend(&list, ft_lstfilenew(entry->d_name));
	return (list);
}

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

void	ft_lstprint_dir(t_file **alst)
{
	t_file *current;

	current = *alst;
	if (!current)
		return ;
	while (current)
	{
		print_dirname((char *)current->filename);
		current = current->next;
	}
}

void	print_dirname(char *filename)
{
	struct stat file;

	if (stat(filename, &file) < 0)
		return ;
	if ((S_ISDIR(file.st_mode)))
	{
		ft_putendl(filename);
	}
}

void	print_files(char *dirname)
{
	struct stat file;
	struct dirent *entry;
	DIR *dfd;

	if ((dfd = opendir(dirname)) == NULL)
		return ;
	while ((entry = readdir(dfd)) != NULL)
		(&list, ft_lstfilenew(entry->d_name));

	if (stat(filename, &file) < 0)
		return ;
	if ((S_ISDIR(file.st_mode)))
	{
		ft_putstr("./");
		ft_putstr(filename);
		ft_putendl(":");
	}
}

void	print_l_format(char *filename)
{
	struct stat file;
	struct passwd *pwd;
	struct group *grp = NULL;

	if (stat(filename, &file) < 0)
		return ; // TODO: handle error without perror
	if ((pwd = getpwuid(file.st_uid)) && (grp = getgrgid(file.st_gid)) == NULL)
		return ; // TODO: handle error without perror
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
	ft_memdel((void *)pwd);
	ft_memdel((void *)grp);
}
