# include "minishell.h"


void	ft_lstadd_back_parse(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = ft_lstlast_parse(*lst);
			tmp->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}

t_cmd	*ft_lstlast_parse(t_cmd *lst)
{
	if ((void *)0 == lst)
		return ((void *)0);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_cmd	*ft_lstnew_parse(void *content)
{
	t_cmd	*new_list;

	new_list = (t_cmd *)malloc(sizeof(t_cmd));
	if ((void *)0 == new_list)
		return ((void *)0);
	new_list->args = content;
	new_list->pipe_in = default_pipe_in;
	new_list->pipe_out = default_pipe_out;
	new_list->next = (void *)0;
	// new_list->mshell = &shell;
	return (new_list);
}