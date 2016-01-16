#include "ft_ls.h"
#include "../libft/includes/libft.h"
void    sort_args(int ac, char **av)
{
    t_list *list;

    list = NULL;
    while (ac-- > 1)
        ft_lstappend(&list, ft_lstnew(av[ac], ft_strlen(av[ac])));
    ft_lstmergesort(&list);
    ft_lstprint(&list);
    ft_lstdelmem(&list, ft_memdel);
}
