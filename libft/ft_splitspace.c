
char			**ft_splitspace(char const *s, char c)
{
	char	**new;
	size_t	len;
	size_t	i;
	size_t	strlen;

	if (!s)
		return (NULL);
	i = 0;
	strlen = 0;
	len = size_to_allocate(s, c);
	new = (char **)ft_memalloc(len + 1);
	if (!new)
		return (NULL);
	while (len--)
	{
		while (*s == c)
			s++;
		strlen = ft_strlenchr(s, c);
		new[i] = ft_strnew(strlen);
		ft_memcpy(new[i], s, strlen);
		s += strlen;
		i++;
	}
	new[i] = NULL;
	return (new);
}
