#include "includes/libft.h"

int main()
{
	t_list *list;

	list = NULL;
	ft_lstappend(&list, ft_lstnew((void *)"Hello", 5));
	ft_lstappend(&list, ft_lstnew((void *)"SALUT", 5));
	ft_lstappend(&list, ft_lstnew((void *)"Sup!", 4));

	ft_lstprint(&list);
	ft_putendl("second wave");
	ft_lstprint(&list);
	ft_putendl("thrird wave");
	ft_lstprint(&list);
	ft_lstdelmem(&list, &ft_memdel);
	ft_putendl("thrird wave");
	if (list == NULL)
		ft_putendl("NULL");
	ft_lstprint(&list);
}
