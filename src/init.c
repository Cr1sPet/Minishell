#include "minishell.h"

void	sort_export(t_env_store	*export, int len)
{
	int			i;
	int			j;
	t_env_store	temp;
	char		*a;
	char		*b;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			a = export[j].key;
			b = export[j + 1].key;
			if (ft_strcmp(a, b) > 0)
			{
				temp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// int	get_shlvl(void)
// {
// 	char	*val;

// 	val = get_env("SHLVL", shell.env);
// 	if (NULL == val)
// 	{
// 		ft_putendl_fd("ERROR WITH MALLOC", shell.stdout);
// 		exit (1);
// 	}
// 	if (check_atoi(val))
// 	{
// 		if (val[0] == '-')
// 			return (0);
// 	}
// 	else
// 		return (1);
// 	return (ft_atoi(val) + 1);
// }

// void	change_shlvl(void)
// {
// 	char		*val;
// 	int			val_int;
// 	int			i;
// 	t_env_store elem;

// 	val_int = get_shlvl();
// 	val = ft_itoa(val_int);
// 	elem.key = "SHLVL";
// 	elem.val = val;
// 	add_env_store(&elem, "1");
// 	shell.env_changed = 0;
// }

t_env_list	*get_env_elem(char *input)
{
	t_env_list	*elem;


	elem = (t_env_list *) malloc (sizeof(t_env_list));
	elem->equal = 0;
	if (NULL == elem)
		exit_with_error("Malloc error");
	elem->key = get_key(input);
	if (NULL == elem->key)
		exit_with_error("Malloc error");
	if (ft_strchr(input, '='))
	{
		elem->val = ft_strdup(ft_strchr(input, '=') + 1);
		if (NULL == elem->val)
			exit_with_error("Malloc error");
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


void	print_env_list(t_env_list *env_list)
{
	while (env_list)
	{
		ft_putstr_fd(env_list->key, 1);
		if (env_list->equal)
		{
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env_list->val, 1);
		}
		env_list = env_list->next;
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
		env[i] = collect_str_env (env_list);
		i++;
		env_list = env_list->next;
	}
	env[i] = NULL;
	return (env);
}


void	initialisation(char **envp)
{
	// int	i;

	// i = 0;
	shell.stdin = dup(STDIN_FILENO);
	shell.stdout = dup (STDOUT_FILENO);
	// get_env_list(&shell.env_list, envp);
	// print_env_list(shell.env_list);
	// clean_cmd_list(shell.env_list);
	// shell.env_changed = 1;
	// change_shlvl();
	// shell.status = 0;
	shell.env_list = NULL;
	get_env_list(&shell.env_list, envp);
	shell.env =  collect_env(shell.env_list);
	// print_env_list(shell.env_list);
}
