#include "minishell.h"

char	*change_value(char *str, char *val)
{
	int		i;
	int		j;
	int		new_size;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	new_size = i + ft_strlen(val) + 1;
	new_str = (char *)malloc(sizeof(char) * new_size);
	if (NULL == new_str)
	{
		ft_putendl_fd("ERROR IN MALLOC", 2);
		exit(1);
	}
	while (j < i)
		new_str[j++] = str[j];
	i = 0;
	while (j < new_size)
		new_str[j++] = val[i++];
	new_str[j] = 0;
	free(str);
	return (new_str);
}

int	find_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	change_old_pwd(t_minishell *mshell)
{

}

void	change_pwd(t_minishell *mshell, char *dest)
{
	int		i;
	char	*pwd;
	char	buf[500];

	pwd = getcwd(buf, sizeof(buf));
	if (!pwd)
	{
		ft_putendl_fd("ERROR WITH GETCWD", 1);
		return ;
	}
	i = 0;
	while (mshell->env[i])
	{
		if (!ft_strncmp(dest, mshell->env[i], 3))
		{
			mshell->env[i] = change_value(mshell->env[i], buf);
			return ;
		}
		i++;
	}
}

void	change_dir(t_minishell *mshell)
{
	int	len;

	len = find_len(mshell->cmd_list->args);
	mshell->status = 0;
	if (len > 2)
	{
		ft_putendl_fd("No such file or directory", 1);
		mshell->status = 1;
	}
	else if (2 == len)
	{
		change_pwd(mshell, "OLDPWD");
		if (-1 == chdir(mshell->cmd_list->args[1]))
		{
			perror("Error");
			mshell->status = 1;
		}
		change_pwd(mshell, "PWD");
	}
}
