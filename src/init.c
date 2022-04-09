/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:14:00 by spurple           #+#    #+#             */
/*   Updated: 2022/04/09 13:28:06 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*get_env_elem(char *input)
{
	t_env_list	*elem;

	elem = (t_env_list *) malloc (sizeof(t_env_list));
	elem->equal = 0;
	if (NULL == elem)
		exit_with_error("minishell: -: malloc error");
	elem->key = get_key(input);
	if (NULL == elem->key)
		exit_with_error("minishell: -: malloc error");
	if (ft_strchr(input, '='))
	{
		elem->val = ft_strdup(ft_strchr(input, '=') + 1);
		if (NULL == elem->val)
			exit_with_error("minishell: -: malloc error");
		elem->equal = 1;
	}
	else
		elem->val = NULL;
	elem->next = NULL;
	return (elem);
}

void	get_env_list(t_env_list **env_list, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		lst_envadd_back(env_list, get_env_elem(envp[i]));
	}
}

int	len_env_list(int mode, t_env_list *env_list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_list)
	{
		if (!env_list->equal)
			j++;
		i++;
		env_list = env_list->next;
	}
	if (1 == mode)
		return (i);
	else
		return (i - j);
}

char	**collect_env(t_env_list *env_list)
{
	int		i;
	int		len;
	char	**env;

	i = 0;
	len = len_env_list(0, g_shell.env_list);
	env = (char **)malloc (sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (env_list->equal)
			env[i] = collect_str_env (env_list);
		i++;
		env_list = env_list->next;
	}
	env[i] = NULL;
	return (env);
}

void	initialisation(char **envp)
{
	g_shell.fd_read = -10;
	g_shell.fd_write = -10;
	g_shell.stdin = dup(STDIN_FILENO);
	g_shell.stdout = dup(STDOUT_FILENO);
	g_shell.status = 0;
	g_shell.env_list = NULL;
	get_env_list(&g_shell.env_list, envp);
	change_shlvl();
	g_shell.env = collect_env(g_shell.env_list);
	set_builtin_funcs(&g_shell);
	set_builtin_names(&g_shell);
}
