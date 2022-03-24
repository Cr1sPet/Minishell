#include "minishell.h"

t_env_store	*get_env_store(char **envp)
{
	int			len;
	int			i;
	t_env_store	*env_store;

	i = 0;
	len = len_2d_str(envp);
	env_store = (t_env_store *) malloc (sizeof(t_env_store) * (len + 1));
	if (NULL == env_store)
	{
		ft_putendl_fd("MALLOC ERROR", shell.stdout);
		exit (1);
	}
	while (envp[i])
	{
		env_store[i].key = get_key(envp[i]);
		if (NULL == env_store)
		{
			ft_putendl_fd("MALLOC ERROR", shell.stdout);
			exit (1);
		}
		env_store[i].val = ft_strdup(ft_strchr(envp[i], '=') + 1);
		env_store[i].equal = 1;
		i++;
	}
	env_store[i].val = NULL;
	env_store[i].key = NULL;
	env_store[i].equal = 0;
	return (env_store);
}

void	print_env_store(t_env_store *env_store)
{
	int	i;

	i = 0;
	while (env_store[i].key)
	{
		ft_putstr_fd(env_store[i].key, 1);
		if (env_store[i].equal)
		{
			ft_putstr_fd("=\"", 1);
			if (env_store[i].val)
				ft_putstr_fd(env_store[i].val, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putendl_fd("", 1);
		i++;
	}
}

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

t_env_store	*get_export(char **envp)
{
	int			i;
	int			len;
	t_env_store	*export;

	i = 0;
	len = len_2d_str(envp);
	export = (t_env_store *) malloc (sizeof(t_env_store) * (len + 1));
	while (shell.env_store[i].key)
	{
		export[i].key = ft_strdup(shell.env_store[i].key);
		export[i].val =  ft_strdup(shell.env_store[i].val);
		export[i].equal = 1;
		i++;
	}
	export[i].val = NULL;
	export[i].key = NULL;
	export[i].equal = 0;
	sort_export(export, len);
	return (export);
}

int	get_shlvl(void)
{
	char	*val;

	val = get_env("SHLVL", shell.env);
	if (NULL == val)
	{
		ft_putendl_fd("ERROR WITH MALLOC", shell.stdout);
		exit (1);
	}
	return (ft_atoi(val));
}

int	find_key_i_env_store(t_env_store *env_store, char *key)
{
	int	i;

	i = 0;
	while (env_store[i].key)
	{
		if (!ft_strcmp(env_store[i].key, key))
			return (i);
		i++;
	}
	return (-1);
}

void	change_shlvl(int flag)
{
	char		*val;
	int			val_int;
	int			i;
	t_env_store elem;

	val_int = get_shlvl();
	if (flag)
		val = ft_itoa(++val_int);
	else
		val = ft_itoa(--val_int);
	elem.key = "SHLVL";
	elem.val = val;
	add_env_store(&elem, "1");
	shell.env_changed = 0;
	// add_elem_to_env_store(&shell.env_store, &elem);
	// add_elem_to_env_store(&shell.export, &elem);
}

void	initialisation(char **envp)
{
	int	i;

	i = 0;
	shell.stdin = dup(STDIN_FILENO);
	shell.stdout = dup (STDOUT_FILENO);
	shell.env_store = get_env_store(envp);
	shell.export = get_export(envp);
	shell.env = collect_env(&shell);
	shell.env_changed = 1;
	change_shlvl(1);
	shell.status = 0;

}
