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

void    insert_files(char *filename, t_list **list)
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
        ft_lstappend(list, ft_lstnew(path, ft_strlen(path)));
        ft_strdel(&path);
	}
    ft_lstmergesort(list);
    closedir(dfd);
}

void    printlist(t_list **list)
{
    t_list *current;

    current = *list;
    while (current != NULL)
    {
		ft_putendl(pathtrim(current->content));
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
	ft_lstdelmem(&list, ft_strdel);
}

void	recurdir(char *fname)
{
	t_list	*list;
	struct stat file;

	list = NULL;
	insert_files(fname, &list);
	foldersofar(fname, &list);
	while (list != NULL)
	{
        if (ft_strcmp(pathtrim(list->content), ".") == 0
        || ft_strcmp(pathtrim(list->content), "..") == 0)
			list = list->next;
		else
		{
			if(stat(list->content, &file) < 0)
			{
				ft_perror(list->content);
				return ;
			}
			if (S_ISDIR(file.st_mode))
				recurdir(list->content);
			list = list->next;
			}
	}
	ft_lstdelmem(&list, ft_strdel);
}
