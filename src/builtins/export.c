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

void	add_val_by_index (t_minishell *mshell, char *val, int index)
{
	if (val)
	{
		mshell->export[index].val = val;
		mshell->export[index].equal = 1;
	}
	else
		mshell->export[index].equal = 0;
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

int	if_key_exists (t_minishell *mshell, t_env_store *elem, int len)
{
	int	i;

	i = 0;
	while (mshell->export[i].key)
	{
		if (!ft_strcmp(mshell->export[i].key, elem->key))
		{
			add_val_by_index(mshell, elem->val, i);
			return 1;
		}
		i++;
	}
	return 0;
}

void	add_elem_to_env_store (t_minishell *mshell, t_env_store *elem)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mshell->export[j].key)
		j++;
	if (if_key_exists(mshell, elem, j))
		return ;
	if (ft_strcmp(elem->key, mshell->export[0].key) < 0)
		mshell->export = add_elem_by_index(mshell->export, elem, 0, j);
	else if (ft_strcmp(elem->key, mshell->export[j - 1].key) > 0)
		mshell->export = add_elem_by_index(mshell->export, elem, j - 1, j);
	else
	{
		while (mshell->export[i].key)
		{
			char *v1 = elem->key;
			char * v2 = mshell->export[i].key;
			char * v3 = mshell->export[i + 1].key;
			if (ft_strcmp(elem->key, mshell->export[i].key) > 0
				&& ft_strcmp(elem->key, mshell->export[i + 1].key) < 0)
				mshell->export =  add_elem_by_index(mshell->export, elem, i + 1, j);
			i++;
		}
	}
}

void	export(char **args, t_minishell *mshell)
{
	int			len;
	int			i;
	int			j;
	t_env_store	temp;

	i = 1;
	j = 0;
	while (mshell->export[j].key)
		j++;
	len = find_len(args);
	mshell->status = 0;
	if (len == 1)
	{
		print_env_store(mshell->export, mshell);
	}
	else if (len > 1)
	{
		while (i < len)
		{
			if ('=' == args[i][0] || '=' == args[i][ft_strlen(args[i]) - 1])
			{
				mshell->status = 1;
				ft_putendl_fd("not a valid identifier", 1);
				i++;
				continue ;
			}
			temp.key = get_key(args[i]);
			temp.val = ft_strchr (args[i], '=');
			if (temp.val)
				temp.val += 1;
			add_elem_to_env_store (mshell, &temp);
			if (ft_strchr(args[i], '='))
			{
				mshell->env_store =  add_elem_by_index(mshell->env_store, &temp, j, j);
			}
			temp.key = NULL;
			temp.val = NULL;
			i++;
		}
	}
}
