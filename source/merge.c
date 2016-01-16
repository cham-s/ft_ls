#include "../libft/includes/libft.h"
#include "ft_ls.h"

void    ft_lstpartition (t_list *head, t_list **front, t_list **back)     
{
    t_list  *fast;
    t_list  *slow;

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

t_list  *ft_mergelists(t_list *a, t_list *b, int (*cmp)())
{
    t_list  *mergedlist;

    mergedlist = NULL;
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    if (cmp((char *)a->content, (char *)b->content) <= 0)
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

void    ft_lstmergesort(t_list **source)
{
    t_list *head;
    t_list *a;
    t_list *b;

    head = *source;
    a = NULL;
    b = NULL;
    if (head == NULL || head->next ==  NULL)
        return ;

    ft_lstpartition(head, &a, &b);
    ft_lstmergesort(&a);
    ft_lstmergesort(&b);
    *source = ft_mergelists(a, b, ft_strcmp);
}
