# include "minishell.h"

char	*get_cmd()
{
	char	*str;

	str = readline("🦍 minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

int	main(int argc, char **argv, char **envp) {
	char *cmd;   

	(void) argv;
	if (1 != argc)
		return (1);
	// signal_init();
	while (1) {
		cmd = get_cmd();
		// cmd = ft_strdup("echo hello | cat -e");
		initialisation(envp);
		parser(cmd, shell.env);
		// if (str_cmd->args[0])
		// 	puts(str_cmd->args[0]);
//		echo(shell.cmd_list->args);
//		shell.cmd_list = shell.cmd_list->next;
		// ft_putstr_fd(*shell.cmd_list->mshell->env, 1);
		exec();
	}
	return 0;
}

