#include "minishell.h"

void	initialisation(t_minishell *mshell, char **envp)
{
	// mshell->cmd_list = NULL;
	init_env(mshell, envp);
	mshell->stdin = dup(STDIN_FILENO);
	mshell->stdout = dup (STDOUT_FILENO);
	mshell->status = 0;
	lst_cmdadd_back(&mshell->cmd_list, lst_cmdnew(mshell));
}
