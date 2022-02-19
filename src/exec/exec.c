#include "minishell.h"

int	is_builtin(t_cmd *cmdlist)
{
	return (0);
}

int	exec_builtin(t_cmd *cmdlist)
{
	return (0);
}

int	exe(t_cmd *cmd_list)
{
	pid_t	child;

	if (cmd_list->redir_in || cmd_list->redir_out)
	{
		if (cmd_list->redir_in == redir_in_1)
			dup2(cmd_list->f1, STDIN_FILENO);
		else if (cmd_list->redir_in == redir_in_2)
		{
			work_here_doc(cmd_list->limiter, cmd_list->f1);
			dup2(cmd_list->f1, STDIN_FILENO);
		}
		if (cmd_list->redir_out == redir_out_1)
			dup2(cmd_list->f2, STDOUT_FILENO);
	}
	child = fork();
	if (-1 == child)
	{
		puts("ERROR IN FORK");
		exit (1);
	}
	else if (0 == child)
	{
		if (-1 == execve(cmd_list->args[0], cmd_list->args, cmd_list->mshell->env))
		{
			puts("ERROR IN EXECVE");
			exit (1);
		}
	}
	else
	{
		waitpid(child, &cmd_list->mshell->status, 0);
		dup2(cmd_list->mshell->stdin, STDIN_FILENO);
		dup2(cmd_list->mshell->stdout, STDOUT_FILENO);
		ft_putnbr_fd(WEXITSTATUS(cmd_list->mshell->status), 1);
	}
	return (1);
}

int	exec(t_cmd *cmd_list)
{
	if (is_builtin(cmd_list))
		exec_builtin(cmd_list);
	else
		exe(cmd_list);
	return (0);
}

