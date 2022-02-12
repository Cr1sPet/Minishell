#include "minishell.h"

void	initialisation(t_minishell *mshell, char **envp)
{
	init_env(mshell, envp);
}