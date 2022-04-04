/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:14:19 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:39:24 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(void)
{
	char	*str;

	str = readline("🦍 minishell> ");
	if (str && *str)
		add_history (str);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	(void) argv;
	if (1 != argc)
		return (1);
	initialisation(envp);
	while (1)
	{	
		signal_init_main();
		cmd = get_cmd();
		parser(cmd);
		g_shell.cmd_list_head = g_shell.cmd_list;
		exec();
		clean_cmd_list(g_shell.cmd_list_head);
		g_shell.cmd_list_head = NULL;
		memclean(g_shell.env, len_2d_str(g_shell.env));
		g_shell.env = collect_env(g_shell.env_list);
	}
	return (0);
}
