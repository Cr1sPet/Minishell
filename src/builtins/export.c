#include "minishell.h"

char	*get_key(char *var)
{
	int	i;

	i = 0;
	if (!ft_strchr(var, '='))
		return (ft_strdup(var));
	while (var[i] != '=')
		i++;
	return (ft_substr(var, 0, i));
}

int		ft_strcmp(char const *s1, char const *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
}

void	add_val_by_index (char *val, int index)
{
	if (val)
	{
		shell.export[index].val = val;
		shell.export[index].equal = 1;
	}
	else
		shell.export[index].equal = 0;
}

t_env_store	*add_elem_by_index (t_env_store *env_store, t_env_store *elem, int index, int len)
{
	int			i;
	int			j;
	t_env_store	*new_env_store;

	i = 0;
	j = 0;
	new_env_store = (t_env_store *)malloc(sizeof(t_env_store) * (len + 2));
	while (i <  len + 1)
	{
		if (i == index)
		{
			new_env_store[i].key = elem->key;
			new_env_store[i].val = elem->val;
			if (new_env_store[i].val)
				new_env_store[i].equal = 1;
			else
				new_env_store[i].equal = 0;
		}	
		else
		{
			new_env_store[i].key = env_store[j].key;
			new_env_store[i].val = env_store[j].val;
			new_env_store[i].equal = env_store[j++].equal;
		}
		i++;
	}
	new_env_store[i].key = NULL;
	new_env_store[i].val = NULL;
	new_env_store[i].equal = 0;
	return new_env_store;
}

int	if_key_exists (t_env_store *elem, int len)
{
	int	i;

	i = 0;
	while (shell.export[i].key)
	{
		if (!ft_strcmp(shell.export[i].key, elem->key))
		{
			add_val_by_index(elem->val, i);
			return 1;
		}
		i++;
	}
	return 0;
}

void	add_elem_to_env_store (t_env_store *elem)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell.export[j].key)
		j++;
	if (if_key_exists(elem, j))
		return ;
	if (ft_strcmp(elem->key, shell.export[0].key) < 0)
		shell.export = add_elem_by_index(shell.export, elem, 0, j);
	else if (ft_strcmp(elem->key, shell.export[j - 1].key) > 0)
		shell.export = add_elem_by_index(shell.export, elem, j - 1, j);
	else
	{
		while (shell.export[i].key)
		{
			char *v1 = elem->key;
			char * v2 = shell.export[i].key;
			char * v3 = shell.export[i + 1].key;
			if (ft_strcmp(elem->key, shell.export[i].key) > 0
				&& ft_strcmp(elem->key, shell.export[i + 1].key) < 0)
				shell.export =  add_elem_by_index(shell.export, elem, i + 1, j);
			i++;
		}
	}
}

void	export()
{
	int			len;
	int			i;
	int			j;
	t_env_store	temp;

	i = 1;
	j = 0;
	while (shell.export[j].key)
		j++;
	len = find_len(shell.cmd_list->args);
	shell.status = 0;
	if (len == 1)
	{
		print_env_store(shell.export);
	}
	else if (len > 1)
	{
		while (i < len)
		{
			if ('=' == shell.cmd_list->args[i][0] || !ft_isalpha(shell.cmd_list->args[i][0]) || \
				'=' == shell.cmd_list->args[i][ft_strlen(shell.cmd_list->args[i]) - 1])
			{
				shell.status = 1;
				ft_putendl_fd("not a valid identifier", 1);
				i++;
				continue ;
			}
			temp.key = get_key(shell.cmd_list->args[i]);
			temp.val = ft_strchr (shell.cmd_list->args[i], '=');
			if (temp.val)
				temp.val += 1;
			add_elem_to_env_store (&temp);
			if (ft_strchr(shell.cmd_list->args[i], '='))
			{
				shell.env_store = add_elem_by_index(shell.env_store, &temp, j, j);
			}
			temp.key = NULL;
			temp.val = NULL;
			i++;
		}
	}
}
