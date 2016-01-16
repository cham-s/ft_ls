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

char    *pathtrim(char *longpath)
{
    return (ft_strrchr(longpath, '/') + 1);
}

void    insert_files(char *filename, t_list **list)
{
	struct dirent *dptr;
	DIR *dfd;
	char path[1024];

	if ((dfd = opendir(filename)) == NULL)
    {
        ft_perror(filename);
        exit (1);
    }
	while ((dptr = readdir(dfd)) != NULL)
    {
        if (ft_strcmp(dptr->d_name, ".") == 0
            || ft_strcmp(dptr->d_name, "..") == 0)
                continue ;
        catpath(filename, dptr->d_name, path);
        ft_lstappend(list, ft_lstnew(path, ft_strlen(path)));
	}
    ft_lstmergesort(list);
    closedir(dfd);
}

static void    print_dots(void)
{
    ft_putendl(".");
    ft_putendl("..");
}

static void    print_path(char *fname)
{
	static int i = 0;

	if (i++ != 0)
		ft_putendl("");
	ft_putstr(fname);
	ft_putendl(":");
}

void    printlist(t_list **list)
{
    t_list *current;

    current = *list;
    while (current != NULL)
    {
        ft_putendl(pathtrim((char *)current->content));
        current = current->next;
    }
}

void     printfiles(char *fname)
{
	t_list *list;

    list = NULL;
    insert_files(fname, &list);
    print_path(fname);
    print_dots();
    printlist(&list);
	ft_lstdelmem(&list, ft_memdel);
}

void    foldersofar(char *fname, t_list **list)
{
    print_path(fname);
    print_dots();
    printlist(list);
}

void	recurdir(char *fname)
{
	t_list	*list;
	struct stat file;

	list = NULL;
	insert_files(fname, &list);
	while (list != NULL)
	{
		if(stat((char *)list->content, &file) < 0)
		{
			ft_perror((char *)list->content);
            exit (1);
		}
		if (S_ISDIR(file.st_mode))
        {
                foldersofar(fname, &list);
			    recurdir((char *)list->content);
        }
		else
			ft_putendl(pathtrim((char *)list->content));
		list = list->next;
	}
	ft_lstdelmem(&list, ft_memdel);
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
	ft_putstr(filename);
	ft_putendl("");
}

void	catpath(char *folder, char *file, char *pathbuf)
{
    size_t  len1;
    size_t  len2;
    char    *name;

    len1 = ft_strlen(folder);
    len2 = ft_strlen(file);
    
    if ((name = ft_strnew((len1 + len2) + 1)) == NULL)
        return ;
    ft_memcpy(name, folder, len1);
    name[len1] = '/';
    ft_memcpy((name + len1) + 1, file, len2);
	ft_strcpy(pathbuf, name);
	ft_strdel(&name);
}

void    ft_perror(char *name)
{
    char *merror;

    merror = ft_strjoin("ft_ls: ", name);
    perror(merror);
    ft_strdel(&merror);
}
