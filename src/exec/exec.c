#include "minishell.h"

int	exe(t_cmd *cmd_list)
{
	pid_t	child;
	int		status;

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
		// ft_putnbr_fd(shell.status, shell.stdout);
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
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args);
	else
		return (0);
	return (1);
}

int	set_fd(t_cmd *cmd_list, int *ok)
{
	*ok = 0;
	// if (cmd_list->redir_in)
	// {
	// 	*ok = 1;
	// 	if (!set_redir_in(cmd_list->redir_in))
	// 		return (-10);
	// }
	if (cmd_list->pipe_in == pipe_in)
	{
		*ok = 1;
		dup2(shell.fds[0], STDIN_FILENO);
		close(shell.fds[0]);
	}
	if (cmd_list->redir_out)
	{
		set_redir_out(cmd_list->redir_out);
		if (*ok == 1)
			*ok = 3;
		else
			*ok = 2;
	}
	else if (cmd_list->pipe_out == pipe_out)
	{
		pipe (shell.fds);
		dup2(shell.fds[1], STDOUT_FILENO);
		close (shell.fds[1]);
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
