#include "minishell.h"


void	del_lst_env_elem(t_env_list *env_list)
{
	free(env_list->key);
	if (env_list->val)
		free(env_list->val);
	free (env_list);
}


void	lst_env_pop(t_env_list **list, char *key)
{
	t_env_list	*temp;
	t_env_list	*prev;

	prev = *list;
	if (!ft_strcmp((*list)->key, key))
	{
		(*list) = (*list)->next;
		del_lst_env_elem(prev);
		return ;
	}
	prev = *list;
	temp = (*list)->next;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
		{
			prev->next = temp->next;
			del_lst_env_elem(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	unset(char **args, t_env_list **env_list)
{
	int		i;

	i = 1;
	while (args[i])
	{
		lst_env_pop(env_list, args[i]);
		i++;
	}
}
