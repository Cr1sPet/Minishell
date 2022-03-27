#include "minishell.h"

static int	add_slash(char ***pathes)
{
	int		i;
	char	*temp;
	char	**temp_pathes;

	i = 0;
	temp_pathes = *pathes;
	while (temp_pathes[i])
	{
		temp = temp_pathes[i];
		temp_pathes[i] = ft_strjoin(temp, "/");
		free(temp);
		if (NULL == temp_pathes[i])
			return (0);
		i++;
	}
	return (1);
}

char	**get_pathes(char **envp)
{
	int		i;
	char	*path;
	char	**pathes;

	i = 0;
	path = NULL;
	path = get_env("PATH", envp);
	if (path)
	{
		pathes = ft_split(path, ':');
		if (pathes && add_slash(&pathes))
		return (pathes);
	}
	return (NULL);
}

static int	set_path(char **cmd, char **pathes)
{
	int		i;
	char	*path;

	i = 0;
	while (pathes[i])
	{
		path = ft_strjoin(pathes[i++], *cmd);
		if (NULL == path)
		{
			// arr_free(pathes);
			return (0);
		}
		if (!access(path, 0))
		{
			free(*cmd);
			*cmd = path;
			return (1);
		}
		free(path);
	}
	return (-1);
}

static int	get_cmd(char **args, char **pathes)
{
	int		ok;

	ok = set_path (&args[0], pathes);
	if (0 == ok)
	{
		ft_putendl_fd("MALLOC ERROR", 2);
		exit (1);
	}
	// else if (-1 == ok)
	// {
	// 	ft_putstr_fd("command not found: ", shell.stdout);
	// 	ft_putendl_fd(args[0], shell.stdout);
	// 	shell.status = 127;
	// 	ok = 0;
	// }
	return (ok);
}

int	parse_cmds(t_cmd *cmd)
{
	char	**pathes;
	int		ok;

	if ('/' == shell.cmd_list->args[0][0] \
		|| !ft_strncmp(shell.cmd_list->args[0], "../", 3) \
				|| !ft_strncmp(shell.cmd_list->args[0], "./", 2))
		return (1);
	pathes = get_pathes(shell.env);
	if (NULL == pathes)
		return (0);
	ok = get_cmd(cmd->args, pathes);
	memclean(pathes, len_2d_str(pathes) + 1);
	return (ok);
}
