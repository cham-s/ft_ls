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

void	listdir(char *directory, char *options)
{
	t_file *list;

	list = NULL;
	getfiles(directory, &list, options);
	listallfiles(&list, options);
}
void    printlist(t_file **list)
{
    t_file *current;

    current = *list;
    while (current != NULL)
    {
		//ft_putendl(pathtrim(current->filename));
        print_l_format(current->filename); 
        current = current->next;
    }
}

void     printfiles(char *fname)
{
	t_file *list;

    list = NULL;
    insert_files(fname, &list);
    print_path(fname);
    printlist(&list);
}

void	recurdir(char *directory, char *options)
{
	t_file	*list;
	t_file	*tmp;
	struct stat file;
	int static i = 0;

	list = NULL;
	getfiles(directory, &list, options);
	listallfiles(&list, options);
	if (i++ != 0)
		ft_putchar('\n');
	while (list != NULL)
	{
		tmp = list;
        if (ft_strcmp(pathtrim(list->filename), ".") == 0
        || ft_strcmp(pathtrim(list->filename), "..") == 0)
		else
		{
			if(stat(list->filename, &file) < 0)
			{
				ft_perror(list->filename);
				return ;
			}
			if (S_ISDIR(file.st_mode))
				recurdir(list->filename);
		}
		list = list->next;
		free(tmp->filename);
		free(tmp);
	}
}
