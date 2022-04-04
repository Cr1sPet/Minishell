/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:28:14 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 18:55:57 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmds(char *str, int *i, int j)
{
	char	ch;

	ch = str[(*i)];
	while (str[++(*i)] && str[(*i)] != ch)
		;
	return (ft_substr(str, j + 1, *i - j - 1));
}

char	*get_redir(char *str, int *i, char ch)
{
	char	*ret;

	if (str[*i + 1] == ch)
	{
		ret = ft_substr(str, *i, 2);
		++(*i);
	}
	else
		ret = (ft_substr(str, *i, 1));
	return (ret);
}

void	ft_lstadd_back_parse(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = ft_lstlast_parse(*lst);
			tmp->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}

t_cmd	*ft_lstlast_parse(t_cmd *lst)
{
	if ((void *)0 == lst)
		return ((void *)0);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_cmd	*ft_lstnew_parse(void *content)
{
	t_cmd	*new_list;

	new_list = (t_cmd *)malloc(sizeof(t_cmd));
	if ((void *)0 == new_list)
		return ((void *)0);
	new_list->args = content;
	new_list->pipe_in = default_pipe_in;
	new_list->pipe_out = default_pipe_out;
	new_list->redir_in = NULL;
	new_list->redir_out = NULL;
	new_list->next = (void *)0;
	return (new_list);
}
