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

void    getfiles(char *filename, t_file **list, char *options)
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
        ft_lstfileappend(list, ft_lstfilenew(path));
		free(path);
	}
	ft_lstmergesort(list, options);
    closedir(dfd);
}

void	printtotal(t_file **list)
{
	int			result;
	t_file		*current;
	struct stat	file;

	current = *list;
	result = 0;
	while (current != NULL)
	{
		if (stat(current->filename, &file) < 0)
			ft_perror(current->filename);
		result += file.st_blocks;
		current = current->next;
	}
	ft_putstr("total ");
	ft_putnbr(result);
	ft_putendl("");
}

void	listallfiles(t_file **list, char *options, char *directory)
{
	t_file		*current;
	static int	i = 0;

	if (i != 0)
	{
		ft_putstr(directory);
		ft_putendl(":");
	}
	current = *list;
	if (ft_strchr(options, 'l'))
		printtotal(list);
	while (current != NULL)
	{
		if (ft_strchr(options, 'l'))
			print_l_format(current->filename, options);
		else
			ft_putendl(pathtrim(current->filename));
		current = current->next;
	}
	i++;
}

void	listallfilesfree(t_file **list, char *options)
{
	t_file *tmp;

	if (ft_strchr(options, 'a') == NULL)
	{
		tmp = *list;
		while (ft_strcmp(pathtrim((*list)->filename), ".") == 0 ||
			ft_strcmp(pathtrim((*list)->filename), "..") == 0)
		{
			*list = (*list)->next;
			free(tmp->filename);
			free(tmp);
		}
	}
    while (*list != NULL)
    {
		tmp = *list;
		printfile(pathtrim((*list)->filename), options);
        *list = (*list)->next;
		free(tmp->filename);
		free(tmp);
    }
}

void	listdir(char *directory, char *options)
{
	t_file *list;

	list = NULL;
	getfiles(directory, &list, options);
	//free the list after this line
	listallfilesfree(&list, options);
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

	list = NULL;
	getfiles(directory, &list, options);
	listallfiles(&list, options, directory);
	while (list != NULL)
	{
		tmp = list;
        if (ft_strcmp(pathtrim(list->filename), ".") == 0
        || ft_strcmp(pathtrim(list->filename), "..") == 0)
			list = list->next;
		else
		{
			if(stat(list->filename, &file) < 0)
			{
				ft_perror(list->filename);
				return ;
			}
			if (S_ISDIR(file.st_mode))
				recurdir(list->filename, options);
			list = list->next;
		}
		free(tmp->filename);
		free(tmp);
	}
}
