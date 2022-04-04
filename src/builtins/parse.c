/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:05:46 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:44:37 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**get_pathes(t_env_list *env_list)
{
	char	*path;
	char	**pathes;

	path = NULL;
	path = get_env("PATH", env_list);
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
			memclean(pathes, len_2d_str(pathes));
			exit (1);
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
		exit_with_error("minishell: -: malloc error");
	}
	else if (-1 == ok)
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found ", STDERR_FILENO);
		g_shell.status = 127;
		ok = 0;
	}
	return (ok);
}

int	parse_cmds(t_cmd *cmd)
{
	int			ret;
	char		**pathes;
	int			ok;

	ok = 1;
	if (!('/' == g_shell.cmd_list->args[0][0] \
		|| !ft_strncmp(g_shell.cmd_list->args[0], "../", 3) \
				|| !ft_strncmp(g_shell.cmd_list->args[0], "./", 2)))
	{
		pathes = get_pathes(g_shell.env_list);
		if (NULL == pathes)
			return (0);
		ok = get_cmd(cmd->args, pathes);
		memclean(pathes, len_2d_str(pathes));
	}
	ret = file_check(cmd->args[0], 0);
	if (ret != 0)
	{
		g_shell.status = ret;
		ok = 0;
	}
	return (ok);
}
