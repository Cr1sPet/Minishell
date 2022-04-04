/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_envadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:14:04 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:14:05 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_envadd_back(t_env_list **list, t_env_list *new)
{
	t_env_list	*tmp;

	if (list)
	{
		if (*list)
		{
			tmp = lst_envlast(*list);
			tmp->next = new;
		}
		else
		{
			*list = new;
		}
	}
}
