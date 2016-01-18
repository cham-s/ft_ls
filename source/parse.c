#include "ft_ls.h"
#include "../libft/includes/libft.h"

void    usage(char c)
{
    ft_putstr_fd("ft_ls: illegal option -- ", 2);
    ft_putchar_fd(c, 2);
    ft_putendl_fd( "", 2);
    ft_putendl_fd("usage: ft_ls [-Ralr] [file ...]", 2);
    exit (EXIT_FAILURE);
}

static	void	appendfolderlist(t_list **list, int ac, char ***av)
{
    while (ac-- >= 1)
    {
        ft_lstappend(list, ft_lstnew(**av, ft_strlen(**av)));
        (*av)++;
    }
	ft_lstmergesort(list);
}

static	void	check_opt(char ***av, char **optlist, char **options, char **tmp)
{
        (**av)++;
        while (***av)
        {
            if (ft_strchr(*optlist, ***av) == NULL)
                usage(***av);
            else
			{
				if (ft_strchr(*tmp, ***av) == NULL)
				{
					while(**options)
						(*options)++;
					**options = ***av;
				}
			}
            (**av)++;
        }
		(*av)++;
}

char	*ft_getopt(int ac, char **av, char* optlist, t_list **list)
{
	char *options;
	char *tmp;

	options = ft_strnew(OPT_MAX);
	tmp = options;
	if (options == NULL)
		return (NULL);
	av++;
    while (ac-- > 1 && (*av)[0] == '-')
		check_opt(&av, &optlist, &options, &tmp);
	appendfolderlist(list, ac, &av);
	return (tmp);
}

/*void    sort_args(int ac, char **av)
{
    cut_list(list, &args, &files);
    ft_lstmergesort(&args);
    ft_lstmergesort(&files);
    //apply_list(&list);
    ft_lstdelmem(&args, ft_memdel);
    ft_lstdelmem(&files, ft_memdel);
}*/

/*static void    cut_list(t_list *head, t_list **args, t_list **files)
{
    t_list *tmp;

    tmp = NULL;
    if (head == NULL || head->next == NULL)
    {
        *args = head;
        *files = NULL;
    }
    else
    {
        tmp = head;
        while (((char *)tmp->next->content)[0] == '-')
            tmp = tmp->next;
    }
    *args = head;
    *files = tmp->next;
    tmp->next = NULL;
}*/

void    apply_opt(t_list **list)
{
    while (*list)
    {
        recurdir((char *)(*list)->content);
        *list = (*list)->next;
    }
}

/*
t_bool	isinlist(t_list **list, void *data_ref, int (*cmp)(void *s2, void *s2, size_t l))
{
	t_list *current;

	current = *list;
	while (current != NULL)
	{
		if (cmp((char *)data_ref, (char *)current->content, 1) == 0)
			return true;
		current = current->next;
	}
	return false;
}
*/
