size_t	size_to_allocate(const char *s, char c)
{
	size_t	size;

	size = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		while (*s == c)
			s++;
		if ((*s && (*s != c)) && ((*(s + 1) == c) || *(s + 1) == '\0'))
			size++;
		if (*s)
			s++;
	}
	return (size);
}
