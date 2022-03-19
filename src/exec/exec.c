#include "minishell.h"

int	exe(t_cmd *cmd_list)
{
	pid_t	child;

//	if (cmd_list->redir_in != default_redir_in || cmd_list->redir_out != default_redir_out)
//	{
//		if (cmd_list->redir_in == redir_in_1)
//			dup2(cmd_list->f1, STDIN_FILENO);
//		else if (cmd_list->redir_in == redir_in_2)
//		{
//			work_here_doc(cmd_list->limiter, cmd_list->f1);
//			dup2(cmd_list->f1, STDIN_FILENO);
//		}
//		if (cmd_list->redir_out == redir_out_1)
//			dup2(cmd_list->f2, STDOUT_FILENO);
//	}
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
			ft_putendl_fd("ERROR IN EXECVE", cmd_list->mshell->stdout);
			perror("ERROR");
			exit (1);
		}
	}
	// else
	// {
	// 	waitpid(child, &(mshell->status), 0);
	// 	dup2(mshell->stdin, STDIN_FILENO);
	// 	dup2(mshell->stdout, STDOUT_FILENO);
	// 	// ft_putnbr_fd(WEXITSTATUS(mshell->status), 1);
	// }
	return (1);
}

int	try_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		echo(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		change_dir(cmd->mshell);
	else if (!ft_strcmp(cmd->args[0], "env"))
		env(cmd->mshell);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd(cmd->mshell);
	else if (!ft_strcmp(cmd->args[0], "export"))
		export(cmd->args, cmd->mshell);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset(cmd->args, cmd->mshell);
	else
		return (0);
	return (1);
}

int	set_fd (t_cmd *cmd_list, int *ok)
{
	*ok = 0;
	if (cmd_list->pipe_in != default_pipe_in || cmd_list->pipe_out != default_pipe_out)
	{
		if (cmd_list->pipe_in == pipe_in)
		{
			dup2(cmd_list->mshell->fds[0], STDIN_FILENO);
			*ok = 1;
			close(cmd_list->mshell->fds[1]);
		}
		if (cmd_list->pipe_out == pipe_out)
		{
			pipe (cmd_list->mshell->fds);
			// close (fds2[0]);
			dup2(cmd_list->mshell->fds[1], STDOUT_FILENO);
			if (*ok == 1)
				*ok = 3;
			else
				*ok = 2;

			// close(mshell->fds[0]);
		}
	}
	return (1);
}

int	exec(t_cmd *cmd)
{
	int	ok;


	ok = 0;
	while(shell.cmd_list)
	{
		set_fd(shell.cmd_list, &ok);
		if (try_builtin (shell.cmd_list))
		{
			if (ok)
			{
				if (1 == ok || ok == 3)
				{
					// close (cmd->mshell->fds[0]);
					dup2(shell.cmd_list->mshell->stdin, STDIN_FILENO);
				}
				if (2 == ok || ok == 3)
				{
					// close (cmd->mshell->fds[1]);
					dup2(shell.cmd_list->mshell->stdout, STDOUT_FILENO);
				}
			}
			ft_putendl_fd("HHAHAHAHAAHAHHAHA", 1);
			shell.cmd_list = shell.cmd_list->next;
			char *str = shell.cmd_list->args[0];
			continue;
		}
		if ('/' == shell.cmd_list->args[0][0] || !ft_strncmp(shell.cmd_list->args[0], "../", 3)\
			|| !ft_strncmp(shell.cmd_list->args[0], "./", 2))
			exe(shell.cmd_list);
		else if (parse_cmds(shell.cmd_list))
			exe(shell.cmd_list);
		if (1 == ok || ok == 3)
		{
			// close (cmd->mshell->fds[0]);
			dup2(shell.cmd_list->mshell->stdin, STDIN_FILENO);
		}
		if (2 == ok || ok == 3)
		{
			// close (cmd->mshell->fds[1]);    
			dup2(shell.cmd_list->mshell->stdout, STDOUT_FILENO);
		}
		ft_putendl_fd("HHAHAHAHAAHAHHAHA", 1);
		shell.cmd_list = shell.cmd_list->next;
	}
//	shell.cmd_list = shell.cmd_list->next;
	return (0);
}
