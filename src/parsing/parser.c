/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 21:52:05 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 20:06:19 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pipe(int i)
{
	while (g_shell.cmd_list)
	{
		if (i == 0 && g_shell.cmd_list->next)
		{
			g_shell.cmd_list->pipe_in = default_pipe_in;
			g_shell.cmd_list->pipe_out = pipe_out;
		}
		if (i > 0 && g_shell.cmd_list->next)
		{
			g_shell.cmd_list->pipe_in = pipe_in;
			g_shell.cmd_list->pipe_out = pipe_out;
		}
		if (i > 0 && !g_shell.cmd_list->next)
		{
			g_shell.cmd_list->pipe_in = pipe_in;
			g_shell.cmd_list->pipe_out = default_pipe_out;
		}
		i++;
		g_shell.cmd_list = g_shell.cmd_list->next;
	}
}

void	check_pipe(void)
{
	t_cmd	*temp;

	temp = g_shell.cmd_list;
	add_pipe(0);
	g_shell.cmd_list = temp;
}

void	cmd_split(char *str)
{
	int		i;
	char	ch;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			while (str[++i] && str[i] != ch)
				;
		}
		if (str[i] == '|')
			str = pipe_parse(&i, str, 0, 0);
	}
	str = pipe_parse(&i, str, 0, 0);
	free(str);
}

void	*parser(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("Exit Minishell", 2);
		clear_all(&g_shell);
		exit(g_shell.status);
		return (NULL);
	}
	else if (str && str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	else if (!prepars(str) || str[0] == '|')
	{
		free(str);
		error_parser("minishell: syntax error near unexpected token");
		g_shell.status = 1;
	}
	else
	{
		str = correct_str(str, -1, 0);
		cmd_split(str);
		check_pipe();
	}
	return (NULL);
}
