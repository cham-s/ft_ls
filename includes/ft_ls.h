/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 09:45:59 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/18 14:00:36 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_LS_H
# define FT_LS_H
# include "../libft/includes/libft.h"
# include <sys/stat.h>
# define OPT_MAX 5

void	recurdir(char *fname);
void    apply_opt(t_list **list);
char	*ft_getopt(int ac, char **av, char* optlist, t_list **list);
void    printfiles(char *fname);
void	insert_files(char *dirname, t_list **list);
void    ft_perror(char *name);
void    ft_ls(char *name);
char    *catpath(char *folder, char *file);
char    *catfilenames(char *folder, char *file);
void    get_listname(char *dirname, t_list **list);
void	print_l_format(char *filename);
void	print_dirname(char *filename);
void	ft_lstfileprint_l_format(t_list **alst);
void	recurdir(char *fname);
void    ft_lstmergesort(t_list **list);
char    *pathtrim(char *longpath);
void    print_dots(void);
void    print_path(char *fname);
void    foldersofar(char *fname, t_list **list);
void    printlist(t_list **list);
void	print_ctime(char *time);
void	perm_format(struct stat *file);
#endif
