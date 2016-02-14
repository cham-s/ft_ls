/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:26:40 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/07 10:44:48 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

void    nlafterfile(t_file *entry)
{
	struct stat file;

    if (entry->next != NULL)
    {
        if (stat(entry->next->filename, &file) < 0)
            return ;
        if (S_ISDIR(file.st_mode))
            ft_putchar('\n');
    }
}

void	ft_list(char *directory, char *options, int ac, char **av)
{
    static int i = 0;

	// a virer?
    av++;
    ac++;
	if (ft_strchr(options, 'R'))
		recurdir(directory, options);
	else
        listdir(directory, options);
    i++;
}

void    print_errors(t_file **list)
{
	struct stat file;
    t_file *tmp;
    t_bool is_empty;

    is_empty = (list[ERRORS] == NULL? true: false);
    while (list[ERRORS] != NULL)
    {
        tmp = list[ERRORS];
        if (stat(list[ERRORS]->filename, &file) < 0)
            if (lstat(list[ERRORS]->filename, &file) < 0)
                ft_perror(list[ERRORS]->filename);
        list[ERRORS] = list[ERRORS]->next;
        free(tmp->filename);
        free(tmp);
    }
    if (list[DIRS] != NULL && list[FILES] == NULL && is_empty == false)
        ft_putchar('\n');
}

void    print_files(t_file **list, char *options, t_max *maxs)
{
    t_file *tmp;
    t_bool is_empty;

    is_empty = (list[FILES] == NULL? true: false);
    while (list[FILES] != NULL)
    {
        tmp = list[FILES];
        if (ft_strchr(options, 'l'))
            print_l_format((list[FILES])->filename, maxs, true);
        else
            ft_putendl((list[FILES])->filename);
        list[FILES] = list[FILES]->next;
        free(tmp->filename);
        free(tmp);
    }
    if (list[DIRS] != NULL && is_empty == false)
        ft_putchar('\n');
}

void    print_folders(t_file **list, char *options, int ac, char **av)
{
	t_file      *tmp;
    static int  i = 0;

    if (list[DIRS])
    {
        if (i++ == 0 && list[DIRS]->next != NULL)
            printdirnl(list[DIRS]->filename, true);
    }
    i = 0;
    while (list[DIRS] != NULL)
    {
        //if (i++ != 0 && ft_strchr(options, 'R') == NULL)
            //printdirnl((*list)->filename, true);
        tmp = list[DIRS];
        ft_list(list[DIRS]->filename, options, ac, av);
        list[DIRS] = list[DIRS]->next;
        free(tmp->filename);
        free(tmp);
    }
}

void	apply_ft_list(t_file **tablist, char *options, int ac, char **av)
{
    t_max   maxs;
    int     len; 

	if (tablist[ERRORS] == NULL && tablist[FILES] == NULL
            && tablist[DIRS] == NULL)
		ft_list(".", options, ac, av);
	else
	{
        initmax(&maxs);
        browse_list_for_maxs(&tablist[FILES], &maxs, options);
        print_errors(tablist);
        print_files(tablist, options, &maxs);
        print_folders(tablist, options, ac, av);
	}
	free(options);
    len = LIST_SIZE;
    while (len--)
        free(*tablist);
    free(tablist);
}
