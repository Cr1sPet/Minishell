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
			perror("ERROR");
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

void	set_fd(t_cmd *cmd)
{
	// if (cmd.)
}

int	is_bin(char **args)
{

	return (0);
}

int	exec(t_cmd *cmd)
{
	while(cmd)
	{
		// if (cmd->redir_out != default_redir_out)
		
	// if (is_builtin(cmd_list))
	// 	exec_builtin(cmd_list);
	// else
		// if ()
		// set_fd(cmd);
		if ('/' == cmd->args[0][0] || !ft_strncmp(cmd->args[0], "../", 3)\
			|| !ft_strncmp(cmd->args[0], "./", 2))
			exe(cmd->mshell);
		else if (parse_cmds(cmd))
			exe(cmd->mshell);
		ft_putendl_fd("HHAHAHAHAAHAHHAHA", 1);
		cmd = cmd->next;
	}
	return (0);
}
