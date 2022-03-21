#include "minishell.h"

void	pwd()
{
	char	*pwd;
	char	buf[2048];

	pwd = getcwd(buf, sizeof(buf));
	if (pwd)
	{
		ft_putendl_fd(buf, 1);
		shell.status = 0;
	}
	else
	{
		perror("Error");
		ft_putendl_fd("No such file or directory", 1);
		shell.status = 127;
	}
}
