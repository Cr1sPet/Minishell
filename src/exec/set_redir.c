#include "minishell.h"

int	open_redirs(t_cmd *cmd_list)
{
	if (cmd_list->redir_in)
	{
		if (!set_redir_in(cmd_list->redir_in))
			return (0);
	}
	if (cmd_list->redir_out)
	{
		if (!set_redir_out(cmd_list->redir_out))
			return (0);
	}
	return (1);
}

int	fill_temp(t_redir *redir)
{
	int		fds[2];
	pid_t	pid;

	if (-1 == pipe(fds))
		return (-1);
	pid = fork();
	if (0 == pid)
	{
		if (-1 == work_here_doc(redir->filename, fds))
			exit_with_error("minishell: -: malloc error");
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close (fds[1]);
	}
	return (fds[0]);
}

int	set_redir_in(t_redir *redir)
{
	int		fd;
	char	*str;

	fd = -2;
	while (redir)
	{
		if (redir_in_1 == redir->type_redr)
			fd = open(redir->filename, O_RDONLY);
		else if (redir_in_2 == redir->type_redr)
			fd = fill_temp(redir);
		if (-1 == fd)
		{
			print_error(redir->filename, strerror(errno));
			return (0);
		}
		shell.fd_read = dup(fd);
		close (fd);
		redir = redir->next;
	}
	return (1);
}

int	set_redir_out(t_redir *redir)
{
	int		fd;
	char	*str;

	fd = -2;
	while (redir)
	{
		if (-2 != fd)
			close (fd);
		if (redir_out_1 == redir->type_redr)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir_out_2 == redir->type_redr)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (-1 == fd)
		{
			print_error(redir->filename, strerror(errno));
			return (0);
		}
		shell.fd_write = fd;
		redir = redir->next;
	}
	return (1);
}
