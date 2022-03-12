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
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(point, envp[i], ft_strlen(point)))
			return (&envp[i][ft_strlen(point) + 1]);
		i++;
	}
	return (NULL);
}

void	init_env(t_minishell *mshell, char **envp)
{
	int		i;
	int		l;

	l = 0;
	while (envp[l])
		l++;
	mshell->env = (char **)malloc (sizeof (char *) * (l + 1));
	if (NULL == mshell->env)
		exit (1);
	i = -1;
	while (++i < l)
	{
		mshell->env[i] = ft_strdup(envp[i]);
		if (NULL == mshell->env[i])
		{
			memclean(mshell->env, i);
			exit (1);
		}
	}
	mshell->env[i] = NULL;
}		

void	env(t_minishell *mshell)
{
	int	i;

	i = 0;
	if (!mshell->env)
		ft_putendl_fd("Not such file or directory", 2);
	while (mshell->env[i])
		ft_putendl_fd(mshell->env[i++], 1);
	mshell->status = 0;
}
