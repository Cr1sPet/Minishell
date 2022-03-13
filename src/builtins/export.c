#include "minishell.h"

char	*get_key(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (ft_substr(var, 0, i));
}

int	key_cmp(char *var1, char *var2)
{
	char	*key1;
	char	*key2;

	key1 = get_key(var1);
	if (NULL == key1)
	{
		ft_putendl_fd("ERROR WITH MALLOC", 1);
		exit (1);
	}
	key2 = get_key(var2);
	if (NULL == key2)
	{
		ft_putendl_fd("ERROR WITH MALLOC", 1);
		exit (1);
	}
	return (strcmp(key1, key2));
}

void	add_var(t_minishell *mshell, char *str)
{
	int		i;
	int		new_size;
	char	**new_env;

	i = 0;
	new_size = find_len(mshell->env) + 2;
	new_env = (char **)malloc (sizeof(char *) * (new_size));
	if (NULL == new_env)
	{
		ft_putendl_fd("ERROR WITH MALLOC", 1);
		exit (1);
	}
	while (mshell->env[i])
	{
		new_env[i] = ft_strdup(mshell->env[i]);
		if (NULL == new_env[i])
		{
			ft_putendl_fd("ERROR WITH MALLOC", 1);
			exit (1);
		}
		i++;
	}
	new_env[i] = ft_strdup(str);
	if (NULL == new_env[i])
	{
		ft_putendl_fd("ERROR WITH MALLOC", 1);
		exit (1);
	}
	new_env[++i] = NULL;
	memclean(mshell->env, new_size - 1);
	mshell->env = new_env;
}

void swap1(char **str1_ptr, char **str2_ptr)
{
  char *temp = *str1_ptr;
  *str1_ptr = *str2_ptr;
  *str2_ptr = temp;
}  

void	print_sorted_env(char **env)
{
	int	i;
	int	j;
	int	arr_size;
	char	*temp;
	char	**temp_env;

	i = 0;
	j = 0;
	temp_env = cp_2d_arr(env);
	arr_size = find_len(temp_env);
	while (i < arr_size)
	{
		while (j < arr_size - 1 - i)
		{
			int a = key_cmp(temp_env[j], temp_env[j + 1]);
			if (a > 0)
			{
				swap1(&temp_env[j], &temp_env[j + 1]);
				// temp = temp_env[j];
				// temp_env[j] = temp_env[j + 1];
				// temp_env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (temp_env[i])
		ft_putendl_fd(temp_env[i++], 1);
	memclean(temp_env, arr_size + 1);
}
void	export(char **args, t_minishell *mshell)
{
	int	len;
	int	i;

	i = 1;
	len = find_len(args);
	mshell->status = 0;
	if (len == 1)
	{
		print_sorted_env(mshell->env);
	}
	else if (len > 1)
	{
		while (i < len)
		{
			if (ft_strchr(args[i], '='))
			{
				if ('=' == args[i][0] || '=' == args[i][ft_strlen(args[i]) - 1])
				{
					mshell->status = 1;
					ft_putendl_fd("not a valid identifier", 1);
					return ;
				}
				add_var(mshell, args[i]);
			}
			i++;
		}
	}
}
