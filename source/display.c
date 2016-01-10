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
#include <time.h>

t_file	*get_filename(char *dirname)
{
	t_file	*list;
	t_file	*under;
	struct stat file;
	struct dirent *entry;
	DIR *dfd;

	list = NULL;
	under = NULL;
	if ((dfd = opendir(dirname)) == NULL)
		return (NULL);
	while ((entry = readdir(dfd)) != NULL)
	{
		under = ft_lstfileappend(&list, ft_lstfilenew(entry->d_name));
		if (stat(under->filename, &file) < 0)
			return (NULL);
		if (S_ISDIR(file.st_mode))
			under->dirlist = get_filename(under->filename);
	}
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
		print_dirname(current->filename);
		current = current->next;
	}
}

void	print_dirname(char *filename)
{
	struct stat file;

	if (stat(filename, &file) < 0)
		return ;
	if ((S_ISDIR(file.st_mode)))
		ft_putendl(filename);
}

void	print_ctime(char *time)
{
	int len;
	len = ft_strlenchr(time, '\n');
	write(1, time, len);
}

void	print_l_format(char *filename)
{
	struct stat file;
	struct passwd *pwd;
	struct group *grp = NULL;

	if (stat(filename, &file) < 0)
	{	
		perror("error from stat");
		//return ; // TODO: handle error without perror
	}
	if ((pwd = getpwuid(file.st_uid)) && (grp = getgrgid(file.st_gid)) == NULL)
	{
		perror("error from pwd grp");
		//return ; // TODO: handle error without perror
	}
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
	print_ctime(ctime(&file.st_atime));
	ft_putstr("  ");
	ft_putstr(filename);
	ft_putendl("");
}
