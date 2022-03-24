#include "minishell.h"

void	ft_exit(char **args)
{
	if (len_2d_str(args) > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putendl_fd("too many arguments", STDERR_FILENO);
		shell.status = 1;
		return ;
	}
	if (args[1] != NULL)
	{
		exit (ft_atoi(args[1]));
	}
	change_shlvl(0);
	memclean(shell.env, len_2d_str(shell.env) + 1);
	clean_env_store(shell.env_store, len_env_store(shell.env_store) + 1);
	clean_env_store(shell.export, len_env_store(shell.export) + 1);
	clean_cmd_list();
	exit (shell.status);
}
