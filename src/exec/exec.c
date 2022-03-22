#include "minishell.h"

int	exe(t_cmd *cmd_list)
{
	pid_t	child;
	int		status;

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
		if (-1 == execve(cmd_list->args[0], cmd_list->args, shell.env))
		{
			ft_putendl_fd("ERROR IN EXECVE", shell.stdout);
			perror("ERROR");
			exit (1);
		}
	}
	else if (!shell.cmd_list->next)
	{
		waitpid(child, &status, 0);
		shell.status = WEXITSTATUS(status);
		dup2(shell.stdin, STDIN_FILENO);
		dup2(shell.stdout, STDOUT_FILENO);
		ft_putnbr_fd(shell.status, shell.stdout);
	}
	return (1);
}

int	try_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		change_dir();
	else if (!ft_strcmp(args[0], "env"))
		env();
	else if (!ft_strcmp(args[0], "pwd"))
		pwd();
	else if (!ft_strcmp(args[0], "export"))
		export();
	else if (!ft_strcmp(args[0], "unset"))
		unset(args, shell.env);
	else
		return (0);
	return (1);
}



int	set_fd(t_cmd *cmd_list, int *ok)
{
	*ok = 0;
	if (cmd_list->redir_in)
	{
		if (!set_redir_in(cmd_list->redir_in))
			return (-10);
	}
	else if (cmd_list->pipe_in == pipe_in)
	{
		*ok = 1;
		dup2(shell.fds[0], STDIN_FILENO);
		close(shell.fds[1]);
	}
	if (cmd_list->redir_out)
	{
		set_redir_out(cmd_list->redir_out);
	}
	else if (cmd_list->pipe_out == pipe_out)
	{
		pipe (shell.fds);
		dup2(shell.fds[1], STDOUT_FILENO);
		if (*ok == 1)
			*ok = 3;
		else
			*ok = 2;
	}
	return (1);
}

int	exec(void)
{
	int	ok;

	ok = 0;
	while (shell.cmd_list)
	{
		if (-10 == set_fd(shell.cmd_list, &ok))
		{
			shell.cmd_list = shell.cmd_list->next;
			continue ;
		}
		if (!try_builtin (shell.cmd_list->args))
		{
			if ('/' == shell.cmd_list->args[0][0] || !ft_strncmp(shell.cmd_list->args[0], "../", 3)\
				|| !ft_strncmp(shell.cmd_list->args[0], "./", 2))
				exe(shell.cmd_list);
			else if (parse_cmds(shell.cmd_list))
				exe(shell.cmd_list);
		}
		if (1 == ok || ok == 3)
			dup2(shell.stdin, STDIN_FILENO);
		if (2 == ok || ok == 3)
			dup2(shell.stdout, STDOUT_FILENO);
		shell.cmd_list = shell.cmd_list->next;
	}
	return (0);
}
