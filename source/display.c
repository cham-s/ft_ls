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

void printfile(t_list **alst)
{
	t_list *current;

	current = *alst;
	if (!current)
		return ;
	while (current)
	{
		ft_putendl(ft_strrchr((char *)current->content, '/') + 1);
		current = current->next;
	}
}

void    get_filesname(char *filename, t_list **list)
{
	struct dirent *dptr;
	DIR *dfd;
    struct stat file;
    char *name;
	if ((dfd = opendir(filename)) == NULL)
    {
        ft_perror(filename);
        return ;
    }
	while ((dptr= readdir(dfd)) != NULL)
    {
        if (ft_strcmp(dptr->d_name, ".") == 0
            || ft_strcmp(dptr->d_name, "..") == 0)
            continue ;
        name = catfilenames(filename, dptr->d_name);
        if (stat(name, &file) < 0)
        {
            ft_perror(name);
            return ;
        }
        ft_lstappend(list, ft_lstnew(name, ft_strlen(name)));
        ft_strdel(&name);
	}
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

char    *catfilenames(char *folder, char *file)
{
    size_t  len1;
    size_t  len2;
    char    *name;

    len1 = ft_strlen(folder);
    len2 = ft_strlen(file);
    
    if ((name = ft_strnew((len1 + len2) + 1)) == NULL)
        return (NULL);
    ft_memcpy(name, folder, len1);
    name[len1] = '/';
    ft_memcpy((name + len1) + 1, file, len2);
    return (name);
}

void    ft_perror(char *name)
{
    char *merror;

    merror = ft_strjoin("ft_ls: ", name);
    perror(merror);
    ft_strdel(&merror);
}

void	enterdir(char *dirname, void (*f)(char *name))
{
    char *name;
    char *ccontent;
    t_list  *list;

    list = NULL;
    get_filesname(dirname, &list);

    if (list == NULL)
    {
        perror("couldn't open directory ");
        ft_putendl(dirname);
        return ;
    }
    while (list != NULL)
    {
        ccontent  = (char *)list->content;
        if (ccontent[0] == '.')
               continue ;
        else
        {
            name = catfilenames(dirname, (char *)list->content);
            f(name);
            ft_strdel(&name);
        }
        list = list->next;
    }
    //delete list
}

void    ft_ls(char *name)
{
    //static int i = 0;
    struct stat stbuf;
    if (stat(name, &stbuf) < 0)
    {
        ft_perror(name);
        return ;
    }
	if ((S_ISDIR(stbuf.st_mode)))
    {
        /*if (i++ != 0)
            ft_putendl("");
        ft_putstr(name);
        ft_putendl(":");*/
        enterdir(name, ft_ls);
    }
    else
        ft_putendl(ft_strrchr(name, '/') + 1);
}

void    recur_dir(char *filename)
{
    t_list  *list;

    list = NULL;
    get_filesname(filename, &list);
    while (list != NULL)
    {
        ft_ls((char *)list->content);
        list = list->next;
    }
}
