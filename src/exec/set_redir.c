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
	int	fd;

	fd = open(".temp_minishell", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (-1 == fd)
		return (-1);
	if (-1 == work_here_doc(redir->filename, fd))
	{
		ft_putendl_fd("ERROR WITH MALLOC", shell.stdout);
		exit (1);
	}
	close (fd);
	fd = open(".temp_minishell", O_RDONLY);
	return (fd);
}

int	set_redir_in(t_redir *redir)
{
	int		fd;
	char	*str;

	fd = -2;
	while (redir)
	{
		if (-2 != fd)
			close(fd);
		if (redir_in_1 == redir->type_redr)
			fd = open(redir->filename, O_RDONLY);
		else if (redir_in_2 == redir->type_redr)
			fd = fill_temp(redir);
		if (-1 == fd)
		{
			str = ft_strjoin("minishell: ", redir->filename);
			if (NULL == str)
				exit_with_error("Malloc error");
			perror(str);
			free (str);
			return (0);
		}
		shell.fd_read = fd;
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
			str = ft_strjoin("minishell: ", redir->filename);
			if (NULL == str)
				exit_with_error("Malloc error");
			perror(str);
			free (str);
			return (0);
		}
		shell.fd_write = fd;
		redir = redir->next;
	}
	return (1);
}
