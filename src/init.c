#include "minishell.h"

t_env_list	*get_env_elem(char *input)
{
	t_env_list	*elem;

	elem = (t_env_list *) malloc (sizeof(t_env_list));
	elem->equal = 0;
	if (NULL == elem)
		exit_with_error("minishell: -: malloc error");
	elem->key = get_key(input);
	if (NULL == elem->key)
		exit_with_error("minishell: -: malloc error");
	if (ft_strchr(input, '='))
	{
		elem->val = ft_strdup(ft_strchr(input, '=') + 1);
		if (NULL == elem->val)
			exit_with_error("minishell: -: malloc error");
		elem->equal = 1;
	}
	else
		elem->val = NULL;
	elem->next = NULL;
	return (elem);
}

void	get_env_list(t_env_list **env_list, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		lst_envadd_back(env_list, get_env_elem(envp[i]));
	}
}

int	len_env_list(int mode, t_env_list *env_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_list)
	{
		if (!env_list->equal)
			j++;
		i++;
		env_list = env_list->next;
	}
	if (1 == mode)
		return (i);
	else if (0 == mode)
		return (i - j);
}

char	**collect_env(t_env_list *env_list)
{
	int		i;
	int		len;
	char	**env;

	i = 0;
	len = len_env_list(0, shell.env_list);
	env = (char **)malloc (sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (env_list->equal)
			env[i] = collect_str_env (env_list);
		i++;
		env_list = env_list->next;
	}
	env[i] = NULL;
	return (env);
}

void	initialisation(char **envp)
{
	shell.stdin = dup(STDIN_FILENO);
	shell.stdout = dup(STDOUT_FILENO);
	shell.status = 0;
	shell.env_list = NULL;
	get_env_list(&shell.env_list, envp);
	change_shlvl();
	shell.env = collect_env(shell.env_list);
}
