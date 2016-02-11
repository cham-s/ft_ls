/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 09:45:59 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/09 15:11:37 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <sys/stat.h>
# define OPT_SIZE (sizeof("Ralrt1")) 
# define LIST_SIZE 3
# define SIX_MON 15552000
# define ERRORS 0
# define FILES  1
# define DIRS   2

typedef struct		s_file
{
	char			*filename;
	time_t			date;
	struct s_file	*next;
}					t_file;

typedef struct		s_max
{
	int				lnk;
    int             uid;
    int             gid;
    int             minor;
    int             major;
	int				size;
}					t_max;

void     browse_list_for_maxs(t_file **list, t_max *maxs);
void     getmaxs(char *filename, t_max *maxs);
t_file	*ft_lstfilenew(char *filename);
void	ft_lstfileappend(t_file **file, t_file *new);
void	ft_list(char *filename, char *options, int ac, char **av);
void	getoptions(int ac, char **av, char *options, char* optlist);
void	getdirs(t_file **list, int ac, char **av, char *options);
void	recurdir(char *directory, char *options);
void    getfiles(char *filename, t_file **list, char *options, t_max *maxs);
void	apply_ft_list(t_file **list, char *options, int ac, char **av);
void	listfile(char *filename, char *options);
void	listdir(char *directory, char *options);
void	listallfiles(t_file **list, char *options, char *directory, t_max *maxs);
void    printfile(char *fname, char *options);
void    ft_perror(char *name);
char    *catpath(char *folder, char *file);
void	print_l_format(char *filename, t_max *max, t_bool is_file);
void    ft_lstmergesort(t_file **source, char *options);
char    *pathtrim(char *longpath);
void    print_path(char *fname);
void    printlist(t_file **list);
void	perm_format(struct stat *file);
void	initmax(t_max *maxs);
void	print_space_nbr(int max, long long size);
int		nbrspace(int max);
void    apply_merge(t_file **list, char *options);
void    printdirnl(char *directory, t_bool first);
void	print_ctime(struct timespec *atime);

#endif
