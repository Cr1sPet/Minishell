#include "minishell.h"

int	set_redir_in(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir_in_1 == redir->type_redr)
		{
			fd = open(redir->filename, O_RDONLY);
			if (-1 == fd)
			{
				ft_putendl_fd("No such file or directory", shell.stdout);
				return (0);
			}
			dup2(fd, STDIN_FILENO);
		}
		redir = redir->next;
	}
	return (1);
}

int	set_redir_out(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir_out_1 == redir->type_redr)
			fd = open(redir->filename, O_WRONLY | O_CREAT, 0644);
		else if (redir_out_2 == redir->type_redr)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (-1 == fd)
		{
			ft_putendl_fd("Error in open", shell.stdout);
			exit (1);
		}
		dup2(fd, STDOUT_FILENO);
		close (fd);
		redir = redir->next;
	}
}
