/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 21:52:05 by spurple           #+#    #+#             */
/*   Updated: 2022/04/01 21:52:37 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipe()
{
	t_cmd	*temp;
	int		i;

	i = 0;
	temp = shell.cmd_list;
	while (shell.cmd_list)
	{
		if (i == 0 && shell.cmd_list->next)
		{
			shell.cmd_list->pipe_in = default_pipe_in;
			shell.cmd_list->pipe_out = pipe_out;
		}
		if (i > 0 && shell.cmd_list->next)
		{
			shell.cmd_list->pipe_in = pipe_in;
			shell.cmd_list->pipe_out = pipe_out;
		}
		if (i > 0 && !shell.cmd_list->next)
		{
			shell.cmd_list->pipe_in = pipe_in;
			shell.cmd_list->pipe_out = default_pipe_out;
		}
		i++;
		shell.cmd_list = shell.cmd_list->next;
	}
	shell.cmd_list = temp;
}

void	cmd_split(char *str, char **envp)
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

void	*parser(char *str, char **envp)
{
	if (str == NULL)
	{
		ft_putendl_fd("\nExit Minishell", 2);
		clear_all(&shell);
		exit(shell.status);			
		return NULL;
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
	}
	else
	{
		str = correct_str(str, envp);
		cmd_split(str, envp);
		check_pipe();
	}
	return (NULL);
}
