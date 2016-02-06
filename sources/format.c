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
void    printstat(struct stat *file, char *filename, t_max *maxs)
{
	struct passwd *pwd;
	struct group *grp;

    grp = NULL;
    if ((pwd = getpwuid(file->st_uid)) && (grp = getgrgid(file->st_gid)) == NULL)
        perror("error from pwd grp");
    perm_format(file);
    ft_putstr("  ");
    printwithspace(maxs->lnk, file->st_nlink);
    ft_putstr("  ");
    ft_putstr(pwd->pw_name);
    ft_putstr("  ");
    ft_putstr(grp->gr_name);
    ft_putstr("  ");
    printwithspace(maxs->size, file->st_size);
    ft_putstr("  ");
    print_ctime(ctime(&file->st_mtime));
    ft_putstr("  ");
    ft_putstr(pathtrim(filename));
    if (S_ISLNK(file->st_mode))
        printlinkpath(filename);
    ft_putendl("");
}

void	print_l_format(char *filename, t_max *maxs)
{
	struct stat file;

		if (lstat(filename, &file) < 0)
            return ;
        if (S_ISLNK(file.st_mode))
            printstat(&file, filename, maxs);
        else
        {
            if (stat(filename, &file) < 0)
                return ;
             printstat(&file, filename, maxs);
        }
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
