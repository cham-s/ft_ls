#include "ft_ls.h"
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

void    print_path(char *fname)
{
	static int i = 0;

	if (i++ != 0)
		ft_putendl("");
	ft_putstr(fname);
	ft_putendl(":");
}

void    foldersofar(char *fname, t_file **list)
{
	struct stat file;

	if (lstat(fname, &file) < 0)
	{
		ft_perror(fname);
		exit(EXIT_FAILURE);
	}
	if (!S_ISLNK(file.st_mode))
	{
		print_path(fname);
		printlist(list);
	}
}

void	print_l_format(char *filename)
{
	struct stat file;
	struct passwd *pwd;
	struct group *grp = NULL;

	if (stat(filename, &file) < 0)
		perror("error from stat");
	if ((pwd = getpwuid(file.st_uid)) && (grp = getgrgid(file.st_gid)) == NULL)
		perror("error from pwd grp");
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
	ft_putstr(pathtrim(filename));
	ft_putendl("");
}

void	print_ctime(char *time)
{
    char *end;

    time = ft_strchr(time, ' ') + 1;
    end = ft_strrchr(time, ':');
	write(1, time, (end - time));
}

void	perm_format(struct stat *file)
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
