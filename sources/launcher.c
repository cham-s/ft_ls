#include "ft_ls.h"
#include "../libft/includes/libft.h"

void    apply_opt(t_list **list)
{
    while (*list)
    {
        recurdir((char *)(*list)->content);
        *list = (*list)->next;
    }
}
