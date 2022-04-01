#include "minishell.h"

int	is_builtin(char *arg)
{
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "env")
		|| !ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

static int	get_exec_nmb(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->args[0] && !is_builtin(cmd->args[0]))
			i++;
		cmd = cmd->next;
	}
	return (i);
}

int	len_cmd_list(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

int	init_fds(t_minishell *shell)
{
	int	i;
	int	len_cmd;

	i = 0;
	len_cmd = len_cmd_list(shell->cmd_list);
	if (len_cmd > 1)
	{
		shell->fds = (int **)malloc(sizeof(int *) * len_cmd);
		if (NULL == shell->fds)
			exit_with_error("minishell: malloc error");
		while (i < len_cmd - 1)
		{
			shell->fds[i] = (int *)malloc(sizeof(int) * 2);
			if (-1 == pipe(shell->fds[i]))
			{
				print_error("-", ": pipe() error");
				shell->fds[i] = NULL;
				return (-1);
			}
			i++;
		}
		shell->fds[len_cmd - 1] = NULL;
	}
	return (1);
}

int	get_pids_fds(t_cmd *cmd_list)
{
	int	exec_nmb;
	int	i;

	exec_nmb = 0;
	shell.pids = NULL;
	shell.fds = NULL;
	exec_nmb = get_exec_nmb(cmd_list);
	if (exec_nmb)
	{
		shell.pids = (pid_t *)malloc(sizeof(pid_t) * exec_nmb);
		if (NULL == shell.pids)
			exit_with_error("minishell : malloc error");
	}
	if (-1 == init_fds(&shell))
	{
		i = 0;
		free (shell.pids);
		close_fds(shell.fds);
		while (shell.fds[i])
			free(shell.fds[i++]);
		free(shell.fds);
		return (0);
	}
	return (1);
}
