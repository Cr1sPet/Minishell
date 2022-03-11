#include "minishell.h"

int	size_2d (char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**del_str(char **env, int index)
{
	char	**new_env;
	int		i;
	int		j;
	int		new_size;

	i = 0;
	j = 0;
	new_size = size_2d(env) - 1;
	new_env = (char **)malloc(sizeof(char *) * new_size);
	if (NULL == new_env)
		return (NULL);
	while (i < new_size)
	{
		if (j == index)
			j++;
		new_env[i] = ft_strdup(env[j++]);
		if (NULL == new_env[i++])
			return (NULL);
	}
	new_env[i] = NULL;
	memclean(env, new_size + 1);
	return (new_env);
}

void	unset(t_minishell *mshell)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (mshell->cmd_list->args[i])
	{
		j = get_ind_env(mshell->cmd_list->args[i], mshell->env);
		if (-1 != j)
		{
			mshell->env = del_str(mshell->env, j);
			if (!mshell->env)
			{
				ft_putendl_fd("ERROR IN MALLOC", 2);
				exit(1);
			}
			env(mshell);
		}
		i++;
	}
}
