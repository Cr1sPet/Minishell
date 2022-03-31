# include "minishell.h"

void	exit_with_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}

int	file_check(char *file_path, int mode)
{
	struct stat	stats;

	if (stat(file_path, &stats) == 0)
	{
		if (1 == S_ISDIR(stats.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(file_path, STDERR_FILENO);
			ft_putendl_fd(" Is a directory ", STDERR_FILENO);
			return (126);
		}
	}
	if (mode && !access(file_path, 0))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file_path, STDERR_FILENO);
		ft_putendl_fd(" No such file or directory ", STDERR_FILENO);
		return (127);
	}
	return (0);
}

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

char	*collect_str_env(t_env_list *elem)
{
	char	*str;
	char	*temp;

	temp = ft_strjoin (elem->key, "=");
	str = ft_strjoin (temp, elem->val);
	free (temp);
	return (str);
}
