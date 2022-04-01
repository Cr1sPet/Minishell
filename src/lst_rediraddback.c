#include "minishell.h"

void	lst_rediradd_back(t_redir **redir, t_redir *new)
{
	t_redir	*tmp;

	if (redir)
	{
		if (*redir)
		{
			tmp = lst_redirlast(*redir);
			tmp->next = new;
		}
		else
		{
			*redir = new;
		}
	}
}
