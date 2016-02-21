/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 17:28:45 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/20 19:52:55 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <sys/stat.h>
# define TRIM(longname) (ft_strrchr(longname, '/') + 1)
# define OPTIN(options, c) ft_strchr(options, c)
# define OPTS		"ARSadlrt1"
# define LIST_SIZE	3
# define SIX_MON	15770000	
# define ERRORS		0
# define FILES		1
# define DIRS		2
# define OPT_SIZE (sizeof(OPTS))

typedef struct		s_file
{
	char			*filename;
	time_t			date;
	off_t			size;
	struct s_file	*next;
}					t_file;

typedef struct		s_max
{
	int				lnk;
	int				user;
	int				group;
	int				uid;
	int				gid;
	int				minor;
	int				major;
	int				size;
}					t_max;

void				check_fts_open(char *s);
void				ft_lstpartition(t_file *head, t_file **front, t_file **back);
t_file				*ft_mergelists(t_file *a, t_file *b, int (*cmp)());
t_file				*ft_mergelists_rev(t_file *a, t_file *b, int (*cmp)());
t_file				*ft_mergelists_rev_t(t_file *a, t_file *b);
void				free_content_and_node(t_file *node);
int					check_for_a(t_file *current, char *options);
int					is_dateinrange(time_t atime);
void				print_size(off_t size, t_max *maxs);
void				printstat2(struct stat *file, char *filename,
					t_bool is_file);
void				print_device(dev_t device, t_max *maxs);
t_bool				is_device(mode_t mode);
void				printtotal(t_file **list, char *options);
void				browse_list_for_maxs(t_file **list, t_max *maxs,
													char *options);
void				getmaxs(char *filename, t_max *maxs, char *options);
t_file				*ft_lstfilenew(char *filename);
void				ft_lstfileappend(t_file **file, t_file *new);
void				ft_list(char *filename, char *options);
void				getoptions(int ac, char **av, char *options,
												char *optlist);
void				getdirs(t_file **list, int ac, char **av, char *options);
void				recurdir(char *directory, char *options);
void				getfiles(char *filename, t_file **list, char *options,
															t_max *maxs);
void				apply_ft_list(t_file **list, char *options);
void				listfile(char *filename, char *options);
void				listdir(char *directory, char *options);
void				listallfiles(t_file **list, char *options,
								char *directory, t_max *maxs);
void				printfile(char *fname, char *options);
void				ft_perror(char *name);
char				*catpath(char *folder, char *file);
void				print_l_format(char *filename, t_max *max,
												t_bool is_file);
void				ft_lstmergesort(t_file **source, char *options);
void				print_path(char *fname);
void				perm_format(struct stat *file, char *path);
void				initmax(t_max *maxs);
void				print_space_nbr(int max, long long size);
void				print_space_str(int max, char *str);
int					nbrspace(int max);
void				apply_merge(t_file **list, char *options);
void				printdirnl(char *directory, t_bool first);
void				print_ctime(struct timespec *atime);

#endif
