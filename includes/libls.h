/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 09:45:59 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/05 09:46:20 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBLS_H
# define LIBLS_H
#include "../libft/includes/libft.h"

typedef struct		s_file
{
	char			*filename;
	struct s_file	*next;
	struct s_file	*dirlist;
}					t_file;

t_list	*get_filename(char *dirname);
void	print_l_format(char *filename);
void	print_dirname(char *filename);
void	ft_lstprint_dir(t_list *alst);
void	ft_lstfileappend(t_file **alst, t_file *new);

#endif
