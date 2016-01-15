/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 09:45:59 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/14 16:32:39 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBLS_H
# define LIBLS_H
#include "../libft/includes/libft.h"

void    printfile(t_list **alst);
void    recur_dir(char *filename);
void	insert_files(char *dirname, t_list **list);
void    ft_perror(char *name);
void    ft_ls(char *name);
void	catpath(char *folder, char *file, char *pathbuf);
char    *catfilenames(char *folder, char *file);
void	enterdir(char *dirname, void (*f)(char *name));
void    get_listname(char *dirname, t_list **list);
void	print_l_format(char *filename);
void	print_dirname(char *filename);
void	ft_lstfileprint_l_format(t_list **alst);
void	recurdir(char *fname);
void    ft_lstmergesort(t_list **list);

#endif
