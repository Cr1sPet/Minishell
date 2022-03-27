#include "minishell.h"

char	*get_cmd()
{
	char	*str;

	str = readline("🦍 minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char *cmd;   

	(void) argv;
	if (1 != argc)
		return (1);
	// signal_init();
	initialisation(envp);
	while (1)
	{
		cmd = get_cmd();
		parser(cmd, shell.env);
		exec(shell.cmd_list);
		clean_cmd_list();
	}
	return (0);
}
