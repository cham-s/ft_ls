/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 22:07:14 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/20 18:30:44 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void	ft_lstpartition(t_file *head, t_file **front, t_file **back)
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
		return (b);
	else if (b == NULL)
		return (a);
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
	return (mergedlist);
}

t_file	*ft_mergelists_rev(t_file *a, t_file *b, int (*cmp)())
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
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
	return (mergedlist);
}

t_file	*ft_mergelists_rev_t(t_file *a, t_file *b)
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->date <= b->date)
	{
		mergedlist = a;
		mergedlist->next = ft_mergelists_rev_t(a->next, b);
	}
	else
	{
		mergedlist = b;
		mergedlist->next = ft_mergelists_rev_t(a, b->next);
	}
	return (mergedlist);
}
