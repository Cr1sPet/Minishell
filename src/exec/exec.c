#include "minishell.h"

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

void	close_fds(int	**fds)
{
	int	i;

	i = 0;
	if (fds)
	{
		while (fds[i])
		{
			close(fds[i][0]);
			close(fds[i][1]);
			i++;
		}
		i = 0;
		while (fds[i])
			free(fds[i++]);
		free(fds);
	}
}

void	wait_pids(pid_t	*pids, int nmb)
{
	int	i;
	int	status;

	i = 0;
	if (pids)
	{
		while (i < nmb)
		{
			waitpid(pids[i], &status, 0);
			i++;
		}
		shell.status = WEXITSTATUS(status);
		free(pids);
	}
}

void	cmd_end_works(int **fds, pid_t *pids, int i)
{
	close_fds(fds);
	wait_pids(pids, i);
	dup2(shell.stdin, STDIN_FILENO);
	dup2(shell.stdout, STDOUT_FILENO);
}

int	exe(t_cmd *cmd_list, int i, int j)
{
	// int		status;

	shell.pids[i] = fork();
	if (-1 == shell.pids[i])
		exit_with_error("Fork error");
	else if (0 == shell.pids[i])
	{
		set_fd(cmd_list, j);
		close_fds(shell.fds);
		execve(cmd_list->args[0], cmd_list->args, shell.env);
		perror("ERROR");
		exit (1);
	}
	return (1);
}

int	try_builtin(char **args, int j)
{
	if (is_builtin(args[0]))
		set_fd(shell.cmd_list, j);
	if (!ft_strcmp(args[0], "echo"))
		echo(args, 1);
	else if (!ft_strcmp(args[0], "cd"))
		change_dir();
	else if (!ft_strcmp(args[0], "env"))
		env(args, shell.env_list);
	else if (!ft_strcmp(args[0], "pwd"))
		pwd(1);
	else if (!ft_strcmp(args[0], "export"))
		export(&shell.env_list, args);
	else if (!ft_strcmp(args[0], "unset"))
		unset(args, &shell.env_list);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args);
	else
		return (0);
	if (is_builtin(args[0]))
	{
		dup2(shell.stdin, STDIN_FILENO);
		dup2(shell.stdout, STDOUT_FILENO);
	}
	return (1);
}

void	open_redirs(t_cmd *cmd_list)
{
	if (cmd_list->redir_in)
	{
		set_redir_in(cmd_list->redir_in);
	}
	if (cmd_list->redir_out)
	{
		set_redir_out(cmd_list->redir_out);
	}
}

int	exec(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	get_pids_fds(shell.cmd_list);
	while (shell.cmd_list)
	{
		open_redirs(shell.cmd_list);
		if (shell.cmd_list->args[0] && !try_builtin (shell.cmd_list->args, j))
		{
			if (parse_cmds(shell.cmd_list))
			{
				exe(shell.cmd_list, i, j);
				i++;
			}
		}
		j++;
		shell.cmd_list = shell.cmd_list->next;
		// dup2(shell.stdin, shell.fd_read);
		// dup2(shell.stdout, shell.fd_write);
	}
	cmd_end_works(shell.fds, shell.pids, i);
	return (0);
}
