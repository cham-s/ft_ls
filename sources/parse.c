#include "ft_ls.h"
#include "../libft/includes/libft.h"

static void    usage(char c)
{
    ft_putstr_fd("ft_ls: illegal option -- ", 2);
    ft_putchar_fd(c, 2);
    ft_putendl_fd( "", 2);
    ft_putendl_fd("usage: ft_ls [-Ralrt] [file ...]", 2);
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

