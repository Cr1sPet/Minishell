#include "minishell.h"

t_redir	*lst_redirnew(char *file, int type)
{
	t_redir	*new_list;

	new_list = (t_redir *)malloc(sizeof(t_redir));
	if ((void *)0 == new_list)
		return ((void *)0);
	new_list->filename = file;
	new_list->type_redr = type;
	new_list->next = (void *)0;
	return (new_list);
}
