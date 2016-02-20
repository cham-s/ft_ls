/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 21:24:23 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/19 21:56:26 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>

void			get_group_maxs(struct stat *file, t_max *maxs)
{
	struct group	*grp;

	if ((grp = getgrgid(file->st_gid)) == NULL)
	{
		if (nbrspace(file->st_gid) > maxs->gid)
			maxs->gid = nbrspace(file->st_gid);
	}
	else
	{
		if ((int)ft_strlen(grp->gr_name) > maxs->group)
			maxs->group = (int)ft_strlen(grp->gr_name);
	}
	if (nbrspace(major(file->st_rdev)) > maxs->major)
		maxs->major = nbrspace(major(file->st_rdev));
	if (nbrspace(minor(file->st_rdev)) > maxs->minor)
		maxs->minor = nbrspace(minor(file->st_rdev));
}

void			get_infos_maxs(struct stat *file, t_max *maxs, char *filename, char *name)
{
	struct passwd	*pwd;

	if (lstat(filename, file) < 0)
		if (stat(filename, file) < 0)
			ft_perror(name);
	if (nbrspace(file->st_nlink) > maxs->lnk)
		maxs->lnk = nbrspace(file->st_nlink);
	if (nbrspace(file->st_size) > maxs->size)
		maxs->size = nbrspace(file->st_size);
	if ((pwd = getpwuid(file->st_uid)) == NULL)
	{
		if (nbrspace(file->st_uid) > maxs->uid)
			maxs->uid = nbrspace(file->st_uid);
	}
	else
	{
		if ((int)ft_strlen(pwd->pw_name) > maxs->user)
			maxs->user = (int)ft_strlen(pwd->pw_name);
	}
	get_group_maxs(file, maxs);
}

void			getmaxs(char *filename, t_max *maxs, char *options)
{
	struct stat		file;
	char			*name;

	name = (ft_strrchr(filename, '/') ? TRIM(filename) : filename);
	if (!(!OPTIN(options, 'a') && name[0] == '.')
			|| OPTIN(options, 'd'))
		get_infos_maxs(&file, maxs, filename, name);
	else if (!OPTIN(options, 'a') && OPTIN(options, 'A') &&
			name[1] != '.' && name[1] != '\0')
		get_infos_maxs(&file, maxs, filename, name);
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

	spc = max - (int)ft_strlen(str);
	ft_putstr(str);
	while (spc--)
		ft_putchar(' ');
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
