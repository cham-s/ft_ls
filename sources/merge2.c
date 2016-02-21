#include "ft_ls.h"
#include "libft.h"

t_file	*ft_mergelists_size(t_file *a, t_file *b)
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->size >= b->size)
	{
		mergedlist = a;
		mergedlist->next = ft_mergelists_size(a->next, b);
	}
	else
	{
		mergedlist = b;
		mergedlist->next = ft_mergelists_size(a, b->next);
	}
	return (mergedlist);
}

t_file	*ft_mergelists_rev_s(t_file *a, t_file *b)
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->size <= b->size)
	{
		mergedlist = a;
		mergedlist->next = ft_mergelists_rev_s(a->next, b);
	}
	else
	{
		mergedlist = b;
		mergedlist->next = ft_mergelists_rev_s(a, b->next);
	}
	return (mergedlist);
}

t_file	*ft_mergelists_tim(t_file *a, t_file *b)
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->date >= b->date)
	{
		mergedlist = a;
		mergedlist->next = ft_mergelists_tim(a->next, b);
	}
	else
	{
		mergedlist = b;
		mergedlist->next = ft_mergelists_tim(a, b->next);
	}
	return (mergedlist);
}

void	ft_lstmergesort(t_file **source, char *options)
{
	t_file *head;
	t_file *a;
	t_file *b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	ft_lstpartition(head, &a, &b);
	ft_lstmergesort(&a, options);
	ft_lstmergesort(&b, options);
	if (ft_strchr(options, 'r'))
		if (OPTIN(options, 't') && !OPTIN(options, 'S'))
			*source = ft_mergelists_rev_t(a, b);
		else if (OPTIN(options, 'S'))
			*source = ft_mergelists_rev_s(a, b);
		else
			*source = ft_mergelists_rev(a, b, ft_strcmp);
	else
	{
		if (OPTIN(options, 't') && !OPTIN(options, 'S'))
			*source = ft_mergelists_tim(a, b);
		else if (OPTIN(options, 'S'))
			*source = ft_mergelists_size(a, b);
		else
			*source = ft_mergelists(a, b, ft_strcmp);
	}
}
