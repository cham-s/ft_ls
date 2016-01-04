/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 14:54:05 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/04 18:57:10 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "includes/libft.h" 
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(".")) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			ft_putendl(ent->d_name);
		}
		closedir(dir);
	}
	else
	{
		ft_putendl("error");
	}

	char *filename = "main.c";
	struct stat *tmpstat;

	tmpstat = malloc(sizeof(struct stat));
	stat(filename, tmpstat);
	int size = tmpstat->st_size;
	ft_putnbr(size);
	ft_putendl("");
	free(tmpstat);
}