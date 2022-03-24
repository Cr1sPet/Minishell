# include "minishell.h"


int	len_2d_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	len_env_store(t_env_store *env_store)
{
	int	i;

	i = 0;
	while (env_store[i].key)
		i++;
	return (i);
}

char	*collect_str_env (t_env_store *elem)
{
	char	*str;
	char	*temp;

	temp =  ft_strjoin (elem->key, "=");
	str = ft_strjoin (temp, elem->val);
	free (temp);
	return (str);
}

void	clean_env_store(t_env_store *env_store, int len)
{
	int	i;

	i = 0;
	while (i < len + 1)
	{
		free(env_store[i].val);
		free(env_store[i].key);
	}
	free(env_store);
}

char	**collect_env (t_minishell *mshell)
{
	int		j;
	int		i;
	char	**env;

	i = 0;
	j = len_env_store(mshell->env_store);
	env	= (char **)malloc (sizeof(char *) * (j + 1));
	while (i < j)
	{
		env[i] = collect_str_env (&mshell->env_store[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
