#include "ft_ls.h"
#include "libft.h"

void			browse_list_for_maxs(t_file **list, t_max *maxs,
                                    char *opts)
{
	t_file		*current;	   

	current = *list;
	while (current != NULL)
	{
		getmaxs(current->filename, maxs, opts);
		current = current->next;
	}
}

void			check_fts_open(char *s)
{
	if (ft_strcmp(s, "") == 0)
	{
		ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
}
