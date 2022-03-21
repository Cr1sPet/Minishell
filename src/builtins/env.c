#include "minishell.h"

void	memclean(char **s, size_t l)
{
	size_t	i;

	i = 0;
	while (i < l)
	{
		free (s[i]);
		i++;
	}
	free (s);
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

char	*get_env(char *point, char **envp)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strjoin(point, "=");
	while (envp[i])
	{
		if (0 == ft_strncmp(envp[i], key, ft_strlen(key)))
			return (&envp[i][ft_strlen(point) + 1]);
		i++;
	}
	return (NULL);
}

char	**cp_2d_arr(char **envp)
{
	int		i;
	int		l;
	char	**ret_arr;
	l = 0;
	while (envp[l])
		l++;
	ret_arr = (char **)malloc (sizeof (char *) * (l + 1));
	if (NULL == ret_arr)
		exit (1);
	i = -1;
	while (++i < l)
	{
		ret_arr[i] = ft_strdup(envp[i]);
		if (NULL == ret_arr[i])
		{
			memclean(ret_arr, i);
			exit (1);
		}
	}
	ret_arr[i] = NULL;
	return (ret_arr);
}		

void	env(t_minishell *mshell)
{
	int	i;

	i = 0;
	if (!shell.env)
		ft_putendl_fd("Not such file or directory", 2);
	while (shell.env[i])
		ft_putendl_fd(shell.env[i++], 1);
	shell.status = 0;
}
