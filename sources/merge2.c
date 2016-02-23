/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:41:17 by cattouma          #+#    #+#             */
/*   Updated: 2016/02/22 08:52:09 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

t_file		*ft_mergelists(t_file *a, t_file *b, int (*cmp)(t_file *a, t_file *b))
{
	t_file	*mergedlist;

	mergedlist = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (cmp(a, b))
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

static int	init_sort(t_file **head, t_file ***source, t_file **a, t_file **b)
{
	*head = **source;
	*a = NULL;
	*b = NULL;
	if (*head == NULL || (*head)->next == NULL)
		return (0);
	else
		return (1);
}

void		ft_lstmergesort(t_file **source, char *options)
{
	t_file *head;
	t_file *a;
	t_file *b;

	if (!init_sort(&head, &source, &a, &b))
		return ;
	ft_lstpartition(head, &a, &b);
	ft_lstmergesort(&a, options);
	ft_lstmergesort(&b, options);
	if (ft_strchr(options, 'r'))
		if (OPTIN(options, 't') && !OPTIN(options, 'S'))
			*source = ft_mergelists(a, b, cmptime_rev);
		else if (OPTIN(options, 'S'))
			*source = ft_mergelists(a, b, cmpsize_rev);
		else
			*source = ft_mergelists(a, b, cmpname_rev);
	else
	{
		if (OPTIN(options, 't') && !OPTIN(options, 'S'))
			*source = ft_mergelists(a, b, cmptime);
		else if (OPTIN(options, 'S'))
			*source = ft_mergelists(a, b, cmpsize);
		else
			*source = ft_mergelists(a, b, cmpname);
	}
}
