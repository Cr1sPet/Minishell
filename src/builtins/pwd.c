#include "minishell.h"

void	pwd(char **args)
{
	char	*pwd;
	char	buf[4096];

	pwd = getcwd(buf, sizeof(buf));
	if (pwd && args)
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		shell.status = 0;
	}
	else
	{
		perror("minishell: pwd: ");
		shell.status = 127;
	}
}
