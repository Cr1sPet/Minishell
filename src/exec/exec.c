/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:59:30 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:10:12 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd_out(t_cmd *cmd_list, int i)
{
	if (cmd_list->redir_out)
	{
		dup2(shell.fd_write, STDOUT_FILENO);
		close(shell.fd_write);
	}
	if (cmd_list->pipe_out == pipe_out)
	{
		if (!cmd_list->redir_out)
		{
			dup2(shell.fds[i][1], STDOUT_FILENO);
			close (shell.fds[i][1]);
		}
	}
	if (!cmd_list->next && !shell.cmd_list->redir_out)
	{
		dup2(shell.stdout, STDOUT_FILENO);
	}
}

void	set_fd(t_cmd *cmd_list, int i)
{
	if (cmd_list->redir_in)
	{
		dup2(shell.fd_read, STDIN_FILENO);
		close(shell.fd_read);
	}
	else if (cmd_list->pipe_in == pipe_in)
	{
		if (i > 0)
		{
			dup2(shell.fds[i - 1][0], STDIN_FILENO);
			close(shell.fds[i - 1][0]);
		}
	}
	set_fd_out(cmd_list, i);
}

int	try_builtin(char **args, int j)
{
	int	i;

	i = 0;
	while (shell.builtin_names[i] && ft_strcmp(shell.builtin_names[i], args[0]))
		i++;
	if (shell.builtin_names[i])
	{
		set_fd(shell.cmd_list, j);
		(*shell.builtin_funcs[i])(args);
		dup2(shell.stdin, STDIN_FILENO);
		dup2(shell.stdout, STDOUT_FILENO);
		return (1);
	}
	return (0);
}

void	exe(t_cmd *cmd_list, int i, int j)
{
	char	*str;

	shell.pids[i] = fork();
	signal_init();
	if (-1 == shell.pids[i])
	{
		print_error("-", "fork() error");
		return ;
	}
	else if (0 == shell.pids[i])
	{
		signal_init_here();
		set_fd(cmd_list, j);
		close_fds(shell.fds);
		execve(cmd_list->args[0], cmd_list->args, shell.env);
		str = ft_strjoin("minishell: ", cmd_list->args[0]);
		perror(str);
		free (str);
		exit (126);
	}
}

int	exec(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (0 == get_pids_fds(shell.cmd_list))
		return (0);
	while (shell.cmd_list)
	{
		if (open_redirs(shell.cmd_list) && shell.cmd_list->args[0] \
			&& !try_builtin (shell.cmd_list->args, j))
		{
			if (parse_cmds(shell.cmd_list))
			{
				exe(shell.cmd_list, i, j);
				i++;
			}
		}
		j++;
		shell.cmd_list = shell.cmd_list->next;
	}
	cmd_end_works(shell.fds, shell.pids, i);
	return (0);
}
