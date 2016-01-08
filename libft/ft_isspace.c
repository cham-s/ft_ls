#include "libft.h"

t_bool	ft_isspace(int c)
{
	unsigned char tc;

	tc = (unsigned char)c;
	if (tc == '\t' || tc ==  ' ' || tc == '\r'
		|| tc == '\v' || tc == '\f')
		return (true);
	return (false);
}
