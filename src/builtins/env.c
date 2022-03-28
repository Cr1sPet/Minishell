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

int	get_ind_env(char *point, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(point, envp[i], ft_strlen(point)))
			return (i);
		i++;
	}
	return (-1);
}

// char	*get_env(char *point, char **envp)
// {
// 	int		i;
// 	char	*key;

// 	i = 0;
// 	key = ft_strjoin(point, "=");
// 	while (envp[i])
// 	{
// 		if (0 == ft_strncmp(envp[i], key, ft_strlen(key)))
// 			return (&envp[i][ft_strlen(point) + 1]);
// 		i++;
// 	}
// 	return (NULL);
// }

char	*get_env(char *point, char **envp)
{
	int		i;
	char	*key;

	i = 0;
	while (shell.env_store[i].key)
	{
		if (i == 77)
			i = i;
		key = shell.env_store[i].key; 
		if (!ft_strcmp(key, point))
		{
			char *val = shell.env_store[i].val;
			return (shell.env_store[i].val);
		}
		i++;
	}
	return (NULL);
}

void	env(int	fd)
{
	int	i;

	i = 0;
	if (!shell.env)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	print_env_store(shell.env_store, fd);
	shell.status = 0;
}
