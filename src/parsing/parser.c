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
	if (str && str[0] == '\0')
		return (NULL);
	if (!prepars(str) || str[0] == '|')
		error_parser("Syntax Error");
	else
	{
		str = correct_str(str, envp);
		cmd_split(str, envp);
		check_pipe();
		free(str);
	}
// 	while (shell.cmd_list)
//   {
//       int i = -1;
// 	//   printf("%s<str %d<pipe_int %d<pipe_out \n", shell.cmd_list->args[0], shell.cmd_list->pipe_in, shell.cmd_list->pipe_out);
//       while (shell.cmd_list->args[++i])
// 		{
// 			printf("%s\n", shell.cmd_list->args[i]);
// 			free(shell.cmd_list->args[i]);
// 		}
// 		while (shell.cmd_list->redir_out)
// 		{
// 			printf("%s<struct\n", shell.cmd_list->redir_out->filename);
// 			printf("%d<type\n", shell.cmd_list->redir_out->type_redr);
// 			free(shell.cmd_list->redir_out->filename);
// 			shell.cmd_list->redir_out= shell.cmd_list->redir_out->next;
// 		}
// 				while (shell.cmd_list->redir_in)
// 		{
// 			printf("%s<struct\n", shell.cmd_list->redir_in->filename);
// 			printf("%d<type\n", shell.cmd_list->redir_in->type_redr);
// 			free(shell.cmd_list->redir_in->filename);
// 			shell.cmd_list->redir_in= shell.cmd_list->redir_in->next;
// 		}
// 		 printf("--------------------------------------\n");
//       shell.cmd_list = shell.cmd_list->next;
//   }
	return (NULL);
}
