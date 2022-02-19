#include "minishell.h"

void	initialisation(t_minishell *mshell, char **envp)
{
	init_env(mshell, envp);
	mshell->stdin = dup(STDIN_FILENO);
	mshell->stdout = dup (STDOUT_FILENO);
	mshell->status = 0;
}
