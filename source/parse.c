#include "ft_ls.h"
#include "../libft/includes/libft.h"

void    apply_list(t_list **list)
{
    while (*list)
    {
        printfiles((char *)(*list)->content);
        *list = (*list)->next;
    }
}

void    usage(char *c)
{
    ft_putendl_fd(2, "ft_ls: illegal option -- ");
    ft_putchar_fd(c);
    ft_putendl("");
    ft_putendl_fd(2, "usage: ft_ls [-Ralr] [file ...]");
    exit (EXIT_FAILURE);
}

void    ft_getopt(int ac, char **av, char* optlist, t_list **files)
{
    while (ac-- > 1 && (*av)[0] == '-')
    {
        while (*av)
        {
            (*av)++;
            if (ft_strchr(optlist, *av) == NULL)
                usage(*av);
            else
                ft_lstappend(&list, ft_lstnew(*av, ft_strlen(*av)));

            (*av)++;
        }
        av++;
    }
    while (ac-- > 1)
    {
        ft_lstappend(&list, ft_lstnew(*av, ft_strlen(*av)));
        av++;
    }
}

void    sort_args(int ac, char **av)
{
    cut_list(list, &args, &files);
    ft_lstmergesort(&args);
    ft_lstmergesort(&files);
    //apply_list(&list);
    ft_lstdelmem(&args, ft_memdel);
    ft_lstdelmem(&files, ft_memdel);
}

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

/*void    apply_list(t_list **list)
{
    while (((char *)(*list)->content)[0] == '-')
        *list = (*list)->next;
    while (*list)
    {
        printfiles((char *)(*list)->content);
        *list = (*list)->next;
    }
}*/
