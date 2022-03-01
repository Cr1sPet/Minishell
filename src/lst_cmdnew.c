
#include "minishell.h"

t_cmd	*lst_cmdnew(t_minishell *mshell)
{
	t_cmd	*new_list;

	new_list = (t_cmd *)malloc(sizeof(t_cmd));
	if ((void *)0 == new_list)
		return ((void *)0);
	new_list->f1 = STDIN_FILENO;
	new_list->f2 = STDOUT_FILENO;
	new_list->pipe_in = default_pipe_in;
	new_list->pipe_out = default_pipe_out;
	new_list->redir_in = default_redir_in;
	new_list->redir_out = default_redir_out;
	new_list->args = NULL;
	new_list->limiter = NULL;
	new_list->mshell = mshell;
	new_list->next = (void *)0;
	return (new_list);
}
