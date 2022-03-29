#include "minishell.h"

char	*get_key(char *var)
{
	int	i;

	i = 0;
	if (!ft_strchr(var, '='))
		return (ft_strdup(var));
	while (var[i] != '=')
		i++;
	return (ft_substr(var, 0, i));
}

int	ft_strcmp(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
}

int	try_change_val(t_env_list *env_list, t_env_list *elem)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, elem->key))
		{
			if (!elem->equal || (env_list->val && elem->val
					&& !ft_strcmp(elem->val, env_list->val)))
				return (1);
			if (env_list->val)
				free(env_list->val);
			env_list->val = NULL;
			env_list->equal = 0;
			if (elem->val)
			{
				env_list->val = ft_strdup(elem->val);
				if (NULL == env_list->val)
					exit_with_error("Malloc error");
				env_list->equal = 1;
			}
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

void	export(t_env_list **env_list, char **args)
{
	int			i;
	int			len;
	t_env_list	*elem;
	char		*val;

	i = 0;
	len = len_2d_str(args);
	if (len > 1)
	{
		while (args[++i])
		{
			elem = get_env_elem(args[i]);
			if (elem->val)
				val = ft_strdup(elem->val);
			else
				val = NULL;
			if (!try_change_val(*env_list, elem))
			{
				lst_envadd_back(env_list,
					lst_envnew(ft_strdup(elem->key), val));
			}
			else
				free (val);
			del_lst_env_elem(elem);
		}
	}
}
