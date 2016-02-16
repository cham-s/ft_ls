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

void    apply_merge(t_file **list, char *options)
{
    if (*list == NULL)
        return ;
    if (ft_strchr(options, 't'))
    {
        if (ft_strchr(options, 'r'))
            ft_lstmergesort(list, "r");
        else
            ft_lstmergesort(list, "");
        ft_lstmergesort(list, "t");
    }
    else if (ft_strchr(options, 'r'))
        ft_lstmergesort(list, "r");
    else
        ft_lstmergesort(list, "");
}

void    getfiles(char *filename, t_file **list, char *options, t_max *maxs)
{
	struct dirent   *dptr;
	DIR             *dfd;
    char            *path;

	if ((dfd = opendir(filename)) == NULL)
    {
        ft_perror(filename);
        return ;
    }
	while ((dptr = readdir(dfd)) != NULL)
    {
        path = catpath(filename, dptr->d_name);
        getmaxs(path, maxs, options);
        ft_lstfileappend(list, ft_lstfilenew(path));
		free(path);
	}
    closedir(dfd);
    apply_merge(list, options);
}

void	printtotal(t_file **list, char *options)
{
	int			result;
	t_file		*current;
	struct stat	file;

	current = *list;
	result = 0;
	while (current != NULL)
	{
        if (ft_strchr(options, 'a') == NULL && pathtrim(current->filename)[0] == '.')
        {
            current = current->next;
            continue ;
        }
        if (lstat(current->filename, &file) < 0)
            return ;
        if (S_ISLNK(file.st_mode))
            result += file.st_blocks;
        else
        {
            if (stat(current->filename, &file) < 0)
                return ;
            result += file.st_blocks;
        }
		current = current->next;
	}
	ft_putstr("total ");
	ft_putnbr(result);
	ft_putendl("");
}

void    printdirnl(char *directory, t_bool first)
{
    if (first)
    {
        ft_putstr(directory);
        ft_putendl(":");
    }
    else
    {
        ft_putchar('\n');
        ft_putstr(directory);
        ft_putendl(":");
    }
}

void	listallfiles(t_file **list, char *options, char *directory, t_max *maxs)
{
	t_file		*current;
	static int	i = 0;

	current = *list;
    if (i != 0)
        printdirnl(directory, false);
	if (ft_strchr(options, 'l') && current->next->next != NULL)
		printtotal(list, options);
    else if (ft_strchr(options, 'l') && current->next->next == NULL  && isoptin(options, 'a'))
		printtotal(list, options);
	while (current != NULL)
	{
        if (ft_strchr(options, 'a') == NULL && pathtrim(current->filename)[0] == '.')
        {
            current = current->next;
            continue ;
        }
		if (ft_strchr(options, 'l'))
			print_l_format(current->filename, maxs, false);
		else
			printfile(pathtrim(current->filename), options);
		current = current->next;
	}
	i++;
}
