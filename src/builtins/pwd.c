#include "minishell.h"

void	pwd(t_minishell *mshell)
{
	char	*pwd;

	pwd = get_env("PWD", mshell->env);
	if (pwd)
		ft_putendl_fd(pwd, 1);
	else
		ft_putendl_fd("No such file or directory", 1);
	mshell->status = 127;
}
