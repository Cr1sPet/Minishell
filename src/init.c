#include "minishell.h"

void	initialisation(t_minishell *mshell, char **envp)
{
	// mshell->cmd_list = NULL;
	mshell->env = cp_2d_arr(envp);
	mshell->stdin = dup(STDIN_FILENO);
	mshell->stdout = dup (STDOUT_FILENO);
	mshell->status = 0;
	lst_cmdadd_back(&mshell->cmd_list, lst_cmdnew(mshell));
}
