/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:14:19 by spurple           #+#    #+#             */
/*   Updated: 2022/04/09 12:31:17 by spurple          ###   ########.fr       */
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
	{
		print_error(argv[1], "No such file or directory");
		return (127);
	}
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
	}
	return (0);
}
