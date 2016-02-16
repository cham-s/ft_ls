/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 19:18:15 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/12 16:44:36 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <time.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include <grp.h>

void            browse_list_for_maxs(t_file **list, t_max *maxs, char *options)
{
    t_file      *current;      

    current = *list;
	while (current != NULL)
    {
        getmaxs(current->filename, maxs, options);
        current = current->next;
    }
}

void            getmaxs(char *filename, t_max *maxs, char *options)
{
	struct stat file;
	struct      passwd *pwd;
	struct      group *grp;
    char        *name;

    name = (ft_strrchr(filename, '/')? pathtrim(filename): filename);
    if (!(isoptin(options, 'a') == NULL && name[0] == '.'))
    {
        if (lstat(filename, &file) < 0)
            if (stat(filename, &file) < 0)
                ft_perror(name);
        if (nbrspace(file.st_nlink) > maxs->lnk)
            maxs->lnk = nbrspace(file.st_nlink);
        if (nbrspace(file.st_size) > maxs->size)
            maxs->size = nbrspace(file.st_size);
        if ((pwd = getpwuid(file.st_uid)) == NULL)
		{
            if (nbrspace(file.st_uid) > maxs->uid)
                maxs->uid = nbrspace(file.st_uid);
		}
		else
		{
            if ((int )ft_strlen(pwd->pw_name) > maxs->user)
                maxs->user = (int )ft_strlen(pwd->pw_name);
		}
        if ((grp = getgrgid(file.st_gid)) == NULL)
		{
            if (nbrspace(file.st_gid) > maxs->gid)
                maxs->gid = nbrspace(file.st_gid);
		}
		else
		{
            if ((int )ft_strlen(grp->gr_name) > maxs->group)
                maxs->group = (int )ft_strlen(grp->gr_name);
		}
        if (nbrspace(major(file.st_rdev)) > maxs->major)
            maxs->major = nbrspace(major(file.st_rdev));
        if (nbrspace(minor(file.st_rdev)) > maxs->minor)
            maxs->minor = nbrspace(minor(file.st_rdev));
    }
}

int				nbrspace(int max)
{
	int i;

	i = 0;
	while (max)
	{
		i++;
		max /= 10;
	}
	return (i ? i : 1);
}

void			print_space_nbr(int max, long long size)
{
	int spc;

    spc = max - nbrspace(size);
	while (spc--)
		ft_putchar(' ');
    ft_putnbr(size);
}

void			print_space_str(int max, char *str)
{
	int spc;

    spc = max - (int )ft_strlen(str);
    ft_putstr(str);
	while (spc--)
		ft_putchar(' ');
}

static int		is_dateinrange(time_t atime)
{
	time_t	now;
	long	result;

	result = 0;
	now = time(&now);
	result = atime - now;
	result = (result < 0? -result: result);
	return (result <= SIX_MON);
}

void			print_ctime(struct timespec *atime)
{
	char *strtime; 
	char *end;
	char *hours;
	char *year;

	strtime = ctime(&(atime)->tv_sec);
	year = ft_strrchr(strtime, ' ') + 1;
	strtime = ft_strchr(strtime, ' ') + 1;
	end = ft_strrchr(strtime, ':');
	*end = '\0';
	end = ft_strrchr(strtime, ' ');
	*end = '\0';
	hours = end + 1;
	ft_putstr(strtime);
	ft_putstr(" ");
	if (is_dateinrange(atime->tv_sec))
		ft_putstr(hours);
	else
    {
        ft_putchar(' ');
        while (*year != '\n')
        {
            ft_putchar(*year);
            year++;
        }
    }
}
