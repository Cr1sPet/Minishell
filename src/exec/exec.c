#include "minishell.h"

int	is_builtin(t_cmd *cmdlist)
{
	return (0);
}

int	exec_builtin(t_cmd *cmdlist)
{
	return (0);
}

int	exe(t_minishell *mshell)
{
	pid_t	child;

	if (mshell->cmd_list->redir_in != default_redir_in || mshell->cmd_list->redir_out != default_redir_out)
	{
		if (mshell->cmd_list->redir_in == redir_in_1)
			dup2(mshell->cmd_list->f1, STDIN_FILENO);
		else if (mshell->cmd_list->redir_in == redir_in_2)
		{
			work_here_doc(mshell->cmd_list->limiter, mshell->cmd_list->f1);
			dup2(mshell->cmd_list->f1, STDIN_FILENO);
		}
		if (mshell->cmd_list->redir_out == redir_out_1)
			dup2(mshell->cmd_list->f2, STDOUT_FILENO);
	}
	else if (mshell->cmd_list->pipe_in != default_pipe_in || mshell->cmd_list->pipe_out != default_pipe_out)
	{
		if (mshell->cmd_list->pipe_in == pipe_in)
		{
			dup2(mshell->fds[0], STDIN_FILENO);
			close(mshell->fds[1]);
		}
		if (mshell->cmd_list->pipe_out == pipe_out)
		{
			dup2(mshell->fds[1], STDOUT_FILENO);
			// close(mshell->fds[0]);
		}
	}
	child = fork();
	if (-1 == child)
	{
		puts("ERROR IN FORK");
		exit (1);
	}
	else if (0 == child)
	{
		if (-1 == execve(mshell->cmd_list->args[0], mshell->cmd_list->args, mshell->env))
		{
			ft_putendl_fd("ERROR IN EXECVE", mshell->stdout);
			exit (1);
		}
	}
	else
	{
		waitpid(child, &(mshell->status), 0);
		dup2(mshell->stdin, STDIN_FILENO);
		dup2(mshell->stdout, STDOUT_FILENO);
		// ft_putnbr_fd(WEXITSTATUS(mshell->status), 1);
	}
	return (1);
}

int	exec(t_minishell *mshell)
{
	while(mshell->cmd_list) {
	// if (is_builtin(cmd_list))
		// exec_builtin(cmd_list);
	// else
		exe(mshell);
		mshell->cmd_list = mshell->cmd_list->next;
	}
	return (0);
}

