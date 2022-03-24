# include "minishell.h"


int	len_2d_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	len_env_store(t_env_store *env_store)
{
	int	i;

	i = 0;
	while (env_store[i].key)
		i++;
	return (i);
}

char	*collect_str_env (t_env_store *elem)
{
	char	*str;
	char	*temp;

	temp =  ft_strjoin (elem->key, "=");
	str = ft_strjoin (temp, elem->val);
	free (temp);
	return (str);
}

void	clean_redir_list(t_redir *redir)
{
	t_redir	*temp_list;

	if (redir)
	{
		while (redir)
		{
			temp_list = redir->next;
			free(redir->filename);
			free(redir);
			redir = redir->next;
		}
	}
}

void	clean_cmd_list(void)
{
	t_cmd	*temp_list;

	if (shell.cmd_list)
	{
		while (shell.cmd_list)
		{
			temp_list = shell.cmd_list->next;
			clean_redir_list(shell.cmd_list->redir_in);
			clean_redir_list(shell.cmd_list->redir_out);
			memclean(shell.cmd_list->args, len_2d_str(shell.cmd_list->args));
			free(shell.cmd_list);
			shell.cmd_list = temp_list;
		}
	}
}

void	clean_env_store(t_env_store *env_store, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(env_store[i].val);
		free(env_store[i].key);
		i++;
	}
	free(env_store);
}

char	**collect_env (t_minishell *mshell)
{
	int		j;
	int		i;
	char	**env;

	i = 0;
	j = len_env_store(mshell->env_store);
	env	= (char **)malloc (sizeof(char *) * (j + 1));
	while (i < j)
	{
		env[i] = collect_str_env (&mshell->env_store[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
