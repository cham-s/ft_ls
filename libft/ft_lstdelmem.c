/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelmem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:38:02 by cattouma          #+#    #+#             */
/*   Updated: 2016/01/14 10:48:23 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelmem(t_list **alst, void (*del)(void **))
{
	t_list *victim;

	victim = NULL;
	while (*alst)
	{
		del(&((*alst)->content));
		victim = *alst;
		*alst = (*alst)->next;
		free(victim);
	}
	*alst = NULL;
}
