#include "ft_ls.h"
#include "../libft/includes/libft.h"

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

void    apply_list(t_list **list)
{
    while (*list)
    {
        printfiles((char *)(*list)->content);
        *list = (*list)->next;
    }
}

char    *flags(void)
{
    return (ft_strdup("lRatr"));
}

static void    cut_list(t_list *head, t_list **args, t_list **files)
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
}

void    sort_args(int ac, char **av)
{
    t_list *list;
    t_list *args;
    t_list *files;

    list = NULL;
    args = NULL;
    files = NULL;
    av++;
    while (ac-- > 1)
    {
        ft_lstappend(&list, ft_lstnew(*av, ft_strlen(*av)));
        av++;
    }
    cut_list(list, &args, &files);
    ft_putendl("arguments:");
    ft_lstmergesort(&args);
    ft_lstprint(&args);
    ft_putendl("");
    ft_putendl("files:");
    ft_lstmergesort(&files);
    ft_lstprint(&files);
    apply_list(&list);
    ft_lstdelmem(&args, ft_memdel);
    ft_lstdelmem(&files, ft_memdel);
}
