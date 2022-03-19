# include "minishell.h"

char	*collect_str_env (t_env_store *elem)
{
	char	*str;
	char	*temp;

	temp =  ft_strjoin (elem->key, "=");
	str = ft_strjoin (temp, elem->val);
	free (temp);
	return (str);
}

char	**collect_env (t_minishell *mshell)
{
	int		j;
	int		i;
	char	**env;

	i = 0;
	j = 0;
	while (mshell->env_store[j].key)
		j++;
	env	= (char **)malloc (sizeof(char *) * (j + 1));
	while (i < j)
	{
		env[i] = collect_str_env (&mshell->env_store[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}