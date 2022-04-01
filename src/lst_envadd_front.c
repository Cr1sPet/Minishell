#include "minishell.h"

void	lst_envadd_front(t_env_list **lst, t_env_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = (*lst);
		*lst = new;
	}
}
