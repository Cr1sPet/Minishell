#include "minishell.h"

void	memclean(char **s, size_t l)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (i < l)
		{
			free (s[i]);
			i++;
		}
		free (s);
	}
}

char	*get_env(char *key, t_env_list *env_list)
{
	while (env_list)
	{
		if (!ft_strcmp(key, env_list->key) && env_list->equal)
			return (env_list->val);
		env_list = env_list->next;
	}
	return (NULL);
}

void	env(char **args, t_env_list *env_list)
{
	shell.status = 0;
	print_env_list(env_list);
}
