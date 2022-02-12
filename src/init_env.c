#include "minishell.h"

static void	memclean(char **s, size_t l)
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

void	init_env(t_minishell *mshell, char **envp)
{
	int		i;
	int		l;

	l = 0;
	while (envp[l])
		l++;
	mshell->env = (char **)malloc (sizeof (char *)* (l + 1));
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
