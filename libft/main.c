#include "includes/libft.h"

int main()
{
	char str[] = "-l -R -r";
	char **split = ft_splitspaces(str);
	while(*split)
	{
		ft_putendl(*split);
		split++;
	}
}
