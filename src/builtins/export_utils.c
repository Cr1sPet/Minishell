#include "minishell.h"

int	valid_export(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[0]))
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

static void	swap(t_env_list *a, t_env_list *b)
{
	char	*temp_key;
	char	*temp_val;
	int		temp_equal;

	temp_key = a->key;
	temp_val = a->val;
	temp_equal = a->equal;
	a->key = b->key;
	a->val = b->val;
	a->equal = b->equal;
	b->key = temp_key;
	b->val = temp_val;
	b->equal = temp_equal;
}

t_env_list	*sort_env_list(t_env_list *start)
{
	int			swapped;
	t_env_list	*ptr1;
	t_env_list	*lptr;

	swapped = 1;
	lptr = NULL;
	if (start == NULL)
		return (NULL);
	while (swapped)
	{
		ptr1 = start;
		swapped = 0;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	return (start);
}

t_env_list	*cp_env(t_env_list *env_list)
{
	t_env_list	*export;
	char		*key;
	char		*val;

	export = NULL;
	while (env_list)
	{
		key = ft_strdup(env_list->key);
		if (NULL == key)
			exit_with_error("Malloc error");
		if (env_list->val)
		{
			val = ft_strdup(env_list->val);
			if (NULL == val)
				exit_with_error("Malloc error");
		}
		else
			val = NULL;
		lst_envadd_back(&export, lst_envnew(key, val));
		env_list = env_list->next;
	}
	return (sort_env_list(export));
}