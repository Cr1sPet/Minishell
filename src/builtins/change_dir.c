#include "minishell.h"

int	envlist_chr(char *key, t_env_list *env_list)
{
	while (env_list)
	{
		if (!ft_strcmp(key, env_list->key))
			return (1);
		env_list = env_list->next;
	}
	return (0);
}

void	change_pwd(char *dest)
{
	char		*pwd;
	t_env_list	temp;
	char		buf[4096];

	pwd = getcwd(buf, sizeof(buf));
	if (!pwd)
		return ;
	temp.key = dest;
	temp.val = pwd;
	change_env_val(&temp, &shell.env_list);
}

void	change_dir(char **args)
{
	int	len;

	len = len_2d_str(args);
	shell.status = 0;
	if (len > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 1);
		shell.status = 1;
	}
	else if (2 == len)
	{
		if (envlist_chr("OLDPWD", shell.env_list))
			change_pwd("OLDPWD");
		if (-1 == chdir(args[1]))
		{
			perror(ft_strjoin("minishell: cd: ", args[1]));
			shell.status = 1;
		}
		change_pwd("PWD");
	}
}
