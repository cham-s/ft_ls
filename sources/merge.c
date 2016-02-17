#include "libft.h"
#include "ft_ls.h"

void	ft_lstpartition (t_file *head, t_file **front, t_file **back)	  
{
	t_file	*fast;
	t_file	*slow;

	if (head == NULL || head->next == NULL)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

t_file	*ft_mergelists(t_file *a, t_file *b, int (*cmp)())
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	if (cmp(a->filename, b->filename) <= 0)
	{
		mergedlist = a;
		mergedlist->next = ft_mergelists(a->next, b, cmp);
	}
	else
	{
		mergedlist = b;
		mergedlist->next = ft_mergelists(a, b->next, cmp);
	}
	return mergedlist;
}

t_file	*ft_mergelists_rev(t_file *a, t_file *b, int (*cmp)())
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	if (cmp(a->filename, b->filename) >= 0)
	{
		mergedlist = a;
		mergedlist->next = ft_mergelists_rev(a->next, b, cmp);
	}
	else
	{
		mergedlist = b;
		mergedlist->next = ft_mergelists_rev(a, b->next, cmp);
	}
	return mergedlist;
}

t_file	*ft_mergelists_tim(t_file *a, t_file *b)
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
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
	return mergedlist;
}

void	ft_lstmergesort(t_file **source, char *options)
{
	t_file *head;
	t_file *a;
	t_file *b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next ==  NULL)
		return ;
	ft_lstpartition(head, &a, &b);
	ft_lstmergesort(&a, options);
	ft_lstmergesort(&b, options);
	if (ft_strchr(options, 'r'))
		*source = ft_mergelists_rev(a, b, ft_strcmp);
	else if (ft_strchr(options, 't'))
		*source = ft_mergelists_tim(a, b);
	else
		*source = ft_mergelists(a, b, ft_strcmp);
}
