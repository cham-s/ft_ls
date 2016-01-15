/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/14 16:32:37 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"
#include "../libft/includes/libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

void	listdir(char *fname)
{
	DIR *dir;
	struct dirent *entry;
	char path[1024];

	if ((dir = opendir(fname)) == NULL)
	{
		ft_perror(fname);
		return ;
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_DIR)
		{		
			catpath(fname, entry->d_name, path);
			if (ft_strcmp(entry->d_name, ".") == 0
				|| ft_strcmp(entry->d_name, "..") == 0)
					continue ;
			listdir(path);
		}
		else
			ft_putendl(entry->d_name);
	}
	closedir(dir);
}

int main(int ac, char **av)
{

    //t_list *list = NULL;
	if (ac == 1)
		recurdir(".");
	else
		while (ac-- > 1)
            recurdir(av[ac]);
         
	//listdir(dirname, 0);
	//insert_files(av[1], &list);
	//printfile(&list);
	//ft_lstdelmem(&list, ft_memdel);
}
