
t_file	*ft_lstfilenew(const char *content)
{
	t_file	*fresh;
	size_t	len;

	fresh = (t_file *)malloc(sizeof(t_file));
	if (!fresh)
		return (NULL);
	if (!content)
		fresh->content = NULL;
	else
	{
		len = ft_strlen(content);
		fresh->content = (void *)ft_memalloc(sizeof(len));
		ft_memcpy(fresh->content, content, len);
	}
	fresh->content_size = 0;
	fresh->next = NULL;
	fresh->list = NULL;
	return (fresh);
}


void	ft_lstfileappend(t_file **alst, t_file *new)
{
	t_file *current;

	current = *alst;
	if (!current)
		*alst = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
