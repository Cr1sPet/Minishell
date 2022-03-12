#include "minishell.h"

void	add_var(t_minishell *mshell, char *str)
{
	int		i;
	int		new_size;
	char	**new_env;

	i = 0;
	new_size = find_len(mshell->env) + 2;
	new_env = (char **)malloc (sizeof(char *) * (new_size));
	if (NULL == new_env)
	{
		ft_putendl_fd("ERROR WITH MALLOC", 1);
		exit (1);
	}
	while (mshell->env[i])
	{
		new_env[i] = ft_strdup(mshell->env[i]);
		if (NULL == new_env[i])
		{
			ft_putendl_fd("ERROR WITH MALLOC", 1);
			exit (1);
		}
		i++;
	}
	new_env[i] = ft_strdup(str);
	if (NULL == new_env[i])
	{
		ft_putendl_fd("ERROR WITH MALLOC", 1);
		exit (1);
	}
	new_env[++i] = NULL;
	memclean(mshell->env, new_size - 1);
	mshell->env = new_env;
}

void	export(char **args, t_minishell *mshell)
{
	int	len;
	int	i;

	i = 1;
	len = find_len(args);
	if (len > 1)
	{
		while (i < len)
		{
			if (ft_strchr(args[i], '=')
				&& '=' != args[i][0])
				add_var(mshell, args[i]);
			i++;
		}
	}
}
