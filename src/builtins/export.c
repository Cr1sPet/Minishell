/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:05:41 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:05:42 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	try_change_val(t_env_list *env_list, t_env_list *elem)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, elem->key))
		{
			if (!elem->equal || (env_list->val && elem->val
					&& !ft_strcmp(elem->val, env_list->val)))
				return (1);
			if (env_list->val)
				free(env_list->val);
			env_list->val = NULL;
			env_list->equal = 0;
			if (elem->val)
			{
				env_list->val = ft_strdup(elem->val);
				if (NULL == env_list->val)
					exit_with_error("minishell: -: malloc error");
				env_list->equal = 1;
			}
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

void	change_env_val(t_env_list *elem, t_env_list **env_list)
{
	if (!try_change_val(*env_list, elem))
	{
		lst_envadd_back(env_list,
			lst_envnew(ft_strdup(elem->key), elem->val));
	}
	del_lst_env_elem(elem);
}

void	print_export(t_env_list *env_list)
{
	t_env_list	*export;

	export = cp_env(env_list);
	print_env_list(export, 1);
	clean_env_list(export);
}

void	export(char **args)
{
	int			i;
	t_env_list	*elem;
	int			len;

	i = 0;
	shell.status = 0;
	len = len_2d_str(args);
	if (1 == len)
		print_export(shell.env_list);
	while (len > 1 && args[++i])
	{
		if (!valid_export(args[i]))
		{
			ft_putendl_fd("not a valid identifier", STDERR_FILENO);
			shell.status = 1;
		}
		else
		{
			elem = get_env_elem(args[i]);
			if (!elem)
				exit_with_error("minishell: -: malloc error");
			change_env_val(elem, &shell.env_list);
		}
	}
}
