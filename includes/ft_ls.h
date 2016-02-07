/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 09:45:59 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/07 10:42:56 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <sys/stat.h>
# define OPT_MAX 6

typedef struct		s_file
{
	char			*filename;
	time_t			date;
	struct s_file	*next;
}					t_file;

typedef struct		s_max
{
	int				lnk;
	int				size;
	int             day;
}					t_max;

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
void	print_l_format(char *filename, t_max *max);
void    ft_lstmergesort(t_file **source, char *options);
char    *pathtrim(char *longpath);
void    print_path(char *fname);
void    printlist(t_file **list);
void	print_ctime(char *time);
void	perm_format(struct stat *file);
void	initmax(t_max *maxs);
void	printwithspace(int nbrs, int size);
int		nbrspace(int max);
void    apply_merge(t_file **list, char *options);
void    printdirnl(char *directory, t_bool first);

#endif
