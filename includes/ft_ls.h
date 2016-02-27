/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 17:28:45 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/27 18:02:30 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <sys/stat.h>
# define TRIM(longname) (ft_strrchr(longname, '/') + 1)
# define OPTIN(options, c) ft_strchr(options, c)
# define ADDFLAG	(t_opt, flag) (t_opt.flag = 1)
# define OPTS		"ARSadflprt"
# define LIST_SIZE	3
# define SIX_MON	15770000
# define ERRORS		0
# define FILES		1
# define DIRS		2
# define OPT_SIZE (sizeof(OPTS))

typedef struct		s_file
{
	char			*pathname;
	char			*filename;
	struct stat		*fstat;
	int				ferrno;
	int				errordir;
	t_bool			from_file;
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

typedef struct		s_opt
{
	int				g_a;
	int				g_r;
	int				g_s;
	int				a;
	int				d;
	int				f;
	int				l;
	int				p;
	int				r;
	int				t;
}					t_opt;

extern	t_opt		g_options;

void				addflag(t_opt *options, char c);
void				initopt(t_opt *options);
int					cmpsize(t_file *a, t_file *b);
int					cmpsize_rev(t_file *a, t_file *b);
int					cmpname_rev(t_file *a, t_file *b);
int					cmpname(t_file *a, t_file *b);
int					cmptime(t_file *a, t_file *b);
int					cmptime_rev(t_file *a, t_file *b);
void				check_fts_open(char *s);
void				addstat(char *filename, t_file *new);
void				ft_lstpartition(t_file *h, t_file **front, t_file **back);
t_file				*ft_mergelists(t_file *a, t_file *b, int (*cmp)());
t_file				*ft_mergelists_rev(t_file *a, t_file *b, int (*cmp)());
t_file				*ft_mergelists_rev_t(t_file *a, t_file *b);
void				free_content_and_node(t_file *node);
int					check_for_a(t_file *current);
int					is_dateinrange(time_t atime);
void				print_size(off_t size, t_max *maxs);
void				printstat2(t_file *entry);
void				print_device(dev_t device, t_max *maxs);
t_bool				is_device(mode_t mode);
void				printtotal(t_file **list);
void				browse_list_for_maxs(t_file **list, t_max *maxs);
void				getmaxs(t_file *entry, t_max *maxs);
t_file				*ft_lstfilenew(char *filename);
void				ft_lstfileappend(t_file **file, t_file *new);
void				getoptions(int ac, char **av,
									char *options, char *optlist);
void				getdirs(t_file **list, int ac, char **av);
void				recurdir(t_file *entry);
void				getfiles(t_file *entry, t_file **list, t_max *maxs);
void				apply_ft_list(t_file **list);
void				listfile(t_file *entry);
void				listdir(t_file *entry);
void				listallfiles(t_file **list,
								t_file *entry, t_max *maxs);
void				printfile(t_file *entry);
void				ft_perror(char *name, int errno);
char				*catpath(char *folder, char *file);
void				print_l_format(t_file *entry, t_max *max);
void				ft_lstmergesort(t_file **source, t_opt *options);
void				print_path(char *fname);
void				perm_format(t_file *entry);
void				initmax(t_max *maxs);
void				print_space_nbr(int max, long long size);
void				print_space_str(int max, char *str);
int					nbrspace(int max);
void				apply_merge(t_file **list);
void				printdirnl(char *directory, t_bool first);
void				print_ctime(struct timespec *atime);

#endif
