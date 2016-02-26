/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 21:24:23 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/24 10:58:09 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>

static void			get_group_maxs(t_file *entry, t_max *maxs)
{
	struct group	*grp;

	if ((grp = getgrgid(entry->fstat->st_gid)) == NULL)
	{
		if (nbrspace(entry->fstat->st_gid) > maxs->gid)
			maxs->gid = nbrspace(entry->fstat->st_gid);
	}
	else
	{
		if ((int)ft_strlen(grp->gr_name) > maxs->group)
			maxs->group = (int)ft_strlen(grp->gr_name);
	}
	if (nbrspace(major(entry->fstat->st_rdev)) > maxs->major)
		maxs->major = nbrspace(major(entry->fstat->st_rdev));
	if (nbrspace(minor(entry->fstat->st_rdev)) > maxs->minor)
		maxs->minor = nbrspace(minor(entry->fstat->st_rdev));
}

static void			get_infos_maxs(t_file *entry, t_max *maxs)
{
	struct passwd	*pwd;

	if (entry->ferrno)
		ft_perror(entry->filename, entry->ferrno);
	if (nbrspace(entry->fstat->st_nlink) > maxs->lnk)
		maxs->lnk = nbrspace(entry->fstat->st_nlink);
	if (nbrspace(entry->fstat->st_size) > maxs->size)
		maxs->size = nbrspace(entry->fstat->st_size);
	if ((pwd = getpwuid(entry->fstat->st_uid)) == NULL)
	{
		if (nbrspace(entry->fstat->st_uid) > maxs->uid)
			maxs->uid = nbrspace(entry->fstat->st_uid);
	}
	else
	{
		if ((int)ft_strlen(pwd->pw_name) > maxs->user)
			maxs->user = (int)ft_strlen(pwd->pw_name);
	}
	get_group_maxs(entry, maxs);
}

void			getmaxs(t_file *entry, t_max *maxs)
{
	if (!(!g_options.a && entry->filename[0] == '.')
			|| g_options.d || g_options.f)
		get_infos_maxs(entry, maxs);
	else if (!g_options.a && g_options.A &&
			entry->filename[1] != '.' && entry->filename[1] != '\0')
		get_infos_maxs(entry, maxs);
}

void			print_year(char *s)
{
	ft_putchar(' ');
	while (*s != '\n')
	{
		ft_putchar(*s);
		s++;
	}
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
		print_year(year);
}
