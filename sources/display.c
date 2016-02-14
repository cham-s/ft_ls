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
        // error from stat
        if (S_ISLNK(file.st_mode))
            result += file.st_blocks;
        else
        {
            if (stat(current->filename, &file) < 0)
                return ;
            // error from stat
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
	//if (isoptin(options, 'l'))
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

void	listallfilesfree(t_file **list, char *directory, char *options, t_max *maxs)
{
	t_file      *tmp;
	static int	i = 0;

    if (i++ != 0)
        printdirnl(directory, false);
	if (ft_strchr(options, 'l') && (*list)->next->next != NULL)
		printtotal(list, options);
    while (*list != NULL)
    {
        tmp = *list;
        if (ft_strchr(options, 'a') == NULL && pathtrim((*list)->filename)[0] == '.')
        {
            *list = (*list)->next;
            free(tmp->filename);
            free(tmp);
            continue ;
        }
        if (ft_strchr(options, 'l'))
            print_l_format((*list)->filename, maxs, false);
        else
            printfile(pathtrim((*list)->filename), options);
        *list = (*list)->next;
        free(tmp->filename);
        free(tmp);
    }
}

void	listdir(char *directory, char *options)
{
	t_file	*list;
	t_max	maxs;

	list = NULL;
	initmax(&maxs);
	getfiles(directory, &list, options, &maxs);
	//free the list after this line
	listallfilesfree(&list, directory, options, &maxs);
}

void	listfile(char *filename, char *options)
{
	t_max	maxs;

	initmax(&maxs);
	//getmaxs
	if (ft_strchr(options, 'l'))
		print_l_format(filename, &maxs, true);
	else
		ft_putendl(filename);
}

void    printfile(char *fname, char *options)
{
	if (ft_strchr(options, 'l') == NULL)
		ft_putendl(fname);
}

void	recurdir(char *directory, char *options)
{
	t_file		*list;
	t_file		*tmp;
	struct stat	file;
	t_max		maxs;
    //static int i = 0;

	list = NULL;
	initmax(&maxs);
	getfiles(directory, &list, options, &maxs);
    //if (i++ != 0)
       // exit(4);
	listallfiles(&list, options, directory, &maxs);
	while (list != NULL)
	{
		tmp = list;
        if (ft_strcmp(pathtrim(list->filename), ".") == 0
        || ft_strcmp(pathtrim(list->filename), "..") == 0)
			list = list->next;
		else
		{
            //skip dots todo function
            if (ft_strchr(options, 'a') == NULL && pathtrim(list->filename)[0] == '.')
            {
                list = list->next;
                free(tmp->filename);
                free(tmp);
                continue ;
            }
			if(stat(list->filename, &file) < 0)
                if(lstat(list->filename, &file) < 0)
                    ft_perror(list->filename);
			if (S_ISDIR(file.st_mode))
				recurdir(list->filename, options);
			list = list->next;
		}
		free(tmp->filename);
		free(tmp);
	}
}
