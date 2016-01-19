#include "ft_ls.h"
#include "../libft/includes/libft.h"
#include <stdio.h>

char    *catpath(char *folder, char *file)
{
    size_t  len1;
    size_t  len2;
    char    *name;

    len1 = ft_strlen(folder);
    len2 = ft_strlen(file);
    
    if ((name = ft_strnew((len1 + len2) + 1)) == NULL)
        return (NULL);
    ft_memcpy(name, folder, len1);
    name[len1] = '/';
    ft_memcpy((name + len1) + 1, file, len2);
    return (name);
}

void    ft_perror(char *name)
{
    char *merror;

    merror = ft_strjoin("ft_ls: ", name);
    perror(merror);
    ft_strdel(&merror);
}

char    *pathtrim(char *longpath)
{
    return (ft_strrchr(longpath, '/') + 1);
}

