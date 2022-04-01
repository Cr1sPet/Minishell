#include "minishell.h"

void	pwd(int fd)
{
	char	*pwd;
	char	buf[4096];

	pwd = getcwd(buf, sizeof(buf));
	if (pwd)
	{
		ft_putendl_fd(buf, fd);
		shell.status = 0;
	}
	else
	{
		perror("minishell: pwd: ");
		shell.status = 127;
	}
}
