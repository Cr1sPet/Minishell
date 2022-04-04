/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_envadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:14:06 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:14:07 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_envadd_front(t_env_list **lst, t_env_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = (*lst);
		*lst = new;
	}
}
