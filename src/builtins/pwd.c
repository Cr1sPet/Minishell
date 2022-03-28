#include "minishell.h"

void	pwd(int fd)
{
	char	*pwd;
	char	buf[2048];

	pwd = getcwd(buf, sizeof(buf));
	if (pwd)
	{
		ft_putendl_fd(buf, fd);
		shell.status = 0;
	}
	else
	{
		perror("Error");
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		shell.status = 127;
	}
}
