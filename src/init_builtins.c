/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:13:58 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:13:59 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_builtin_names(t_minishell *shell)
{
	char	*all_builtins;

	all_builtins = ft_strdup("cd env echo exit export pwd unset");
	if (NULL == all_builtins)
		exit_with_error("minishell: -: malloc error");
	shell->builtin_names = ft_split(all_builtins, ' ');
	free(all_builtins);
	if (NULL == shell->builtin_names)
		exit_with_error("minishell: -: malloc error");
}

void	set_builtin_funcs(t_minishell *shell)
{
	shell->builtin_funcs[0] = change_dir;
	shell->builtin_funcs[1] = env;
	shell->builtin_funcs[2] = echo;
	shell->builtin_funcs[3] = ft_exit;
	shell->builtin_funcs[4] = export;
	shell->builtin_funcs[5] = pwd;
	shell->builtin_funcs[6] = unset;
}
