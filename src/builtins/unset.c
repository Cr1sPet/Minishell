/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:13:43 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:43:51 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lst_env_elem(t_env_list *env_list)
{
	free(env_list->key);
	if (env_list->val)
		free(env_list->val);
	free (env_list);
}

void	lst_env_pop(t_env_list **list, char *key)
{
	t_env_list	*temp;
	t_env_list	*prev;

	prev = *list;
	if (!ft_strcmp((*list)->key, key))
	{
		(*list) = (*list)->next;
		del_lst_env_elem(prev);
		return ;
	}
	prev = *list;
	temp = (*list)->next;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
		{
			prev->next = temp->next;
			del_lst_env_elem(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	valid_unset(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]))
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	unset(char **args)
{
	int		i;

	i = 0;
	g_shell.status = 0;
	while (args[i])
	{
		if (!valid_unset(args[i]))
		{
			ft_putendl_fd("not a valid identifier", STDERR_FILENO);
			g_shell.status = 1;
		}
		else
			lst_env_pop(&g_shell.env_list, args[i]);
		i++;
	}
}
