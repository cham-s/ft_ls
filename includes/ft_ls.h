/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 09:45:59 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/01 18:41:54 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <sys/stat.h>
# define OPT_MAX 5

typedef struct		s_file
{
	char			*filename;
	int				date;
	struct s_file	*next;
}					t_file;

t_file	*ft_lstfilenew(char *filename);
void	ft_lstfileappend(t_file **file, t_file *new);
void	ft_list(char *filename, char *options);
void	getoptions(int ac, char **av, char *options, char* optlist);
void	getdirs(t_file **list, int ac, char **av, char *options);
void	recurdir(char *directory, char *options);
void    getfiles(char *filename, t_file **list, char *options);
void	apply_ft_list(t_file **list, char *options);
void	listdir(char *directory, char *options);
void	listallfiles(t_file **list, char *options);
void    printfiles(char *fname);
void	insert_files(char *dirname, t_file **list);
void    ft_perror(char *name);
void    ft_ls(char *name);
char    *catpath(char *folder, char *file);
char    *catfilenames(char *folder, char *file);
void    get_filename(char *dirname, t_file **list);
void	print_l_format(char *filename);
void	print_dirname(char *filename);
void	ft_lstfileprint_l_format(t_file **alst);
void	recurdir(char *fname);
void    ft_lstmergesort(t_file **source, char *options);
char    *pathtrim(char *longpath);
void    print_path(char *fname);
void    foldersofar(char *fname, t_file **list);
void    printlist(t_file **list);
void	print_ctime(char *time);
void	perm_format(struct stat *file);

#endif
