#include "minishell.h"

void	lst_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = lst_cmdlast(*lst);
			tmp->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}
