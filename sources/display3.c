#include "ft_ls.h"
#include "libft.h"

void		printdirnl(char *directory, t_bool first)
{
	if (first)
	{
		ft_putstr(directory);
		ft_putendl(":");
	}
	else
	{
		ft_putchar('\n');
		ft_putstr(directory);
		ft_putendl(":");
	}
}

static void	apply_format(t_file **current, char *options, t_max *maxs)
{
	while (*current != NULL)
	{
		if (check_for_a(*current, options))
		{
			*current = (*current)->next;
			continue ;
		}
		if (ft_strchr(options, 'l'))
			print_l_format((*current)->filename, maxs, false);
		else
			printfile(TRIM((*current)->filename), options);
		*current = (*current)->next;
	}
}

void	listallfiles(t_file **list, char *options, char *directory, t_max *maxs)
{
	t_file		*current;
	static int	i = 0;

	current = *list;
	if (i++ != 0)
		printdirnl(directory, false);
	if (current && current->next)
	{
		if (ft_strchr(options, 'l') && current->next->next)
			printtotal(list, options);
		else if (ft_strchr(options, 'l') &&
				!current->next->next && OPTIN(options, 'a'))
			printtotal(list, options);
	}
	apply_format(&current, options, maxs);
}
