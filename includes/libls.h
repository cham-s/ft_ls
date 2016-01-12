/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 09:45:59 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/09 22:30:55 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBLS_H
# define LIBLS_H
#include "../libft/includes/libft.h"

typedef struct		s_file
{
	char			*filename;
	struct s_file	*next;
    t_bool          is_dir;
}					t_file;

void    ft_perror(char *name);
void    ft_ls(char *name, t_file **list);
char    *catfilenames(char *folder, char *file);
void	enterdir(t_file **list, char *dirname, void (*f)(char *name, t_file **list));
t_file	*get_filename(char *dirname);
void	print_l_format(char *filename);
void	print_dirname(char *filename);
t_file	*ft_lstfilenew(const char *content, t_bool is_dir);
void	ft_lstprint_dir(t_file **alst);
t_file	*ft_lstfileappend(t_file **alst, t_file *new);
void	ft_lstfileprint(t_file **alst);
void	ft_lstfileprint_l_format(t_file **alst);

#endif
