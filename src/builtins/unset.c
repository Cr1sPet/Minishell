#include "minishell.h"

char	**del_str(char **env, int index)
{
	char	**new_env;
	int		i;
	int		j;
	int		new_size;

	i = 0;
	j = 0;
	new_size = find_len(env);
	new_env = (char **)malloc(sizeof(char *) * new_size);
	if (NULL == new_env)
		return (NULL);
	while (j < new_size)
	{
		if (j == index)
		{
			j++;
			if (j != new_size - 1)
				break ;
		}
		new_env[i] = ft_strdup(env[j++]);
		if (NULL == new_env[i++])
			return (NULL);
	}
	new_env[i] = NULL;
	memclean(env, new_size + 1);
	return (new_env);
}

void	unset(char **args, t_minishell *mshell)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (args[i])
	{
		j = get_ind_env(args[i], mshell->env);
		if (-1 != j)
		{
			mshell->env = del_str(mshell->env, j);
			if (!mshell->env)
			{
				ft_putendl_fd("ERROR IN MALLOC", 2);
				exit(1);
			}
		}
		i++;
	}
}
