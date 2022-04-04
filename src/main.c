#include "minishell.h"

char	*get_cmd(void)
{
	char	*str;

	str = readline("🦍 minishell > ");
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
	signal_init();
	initialisation(envp);
	while (1)
	{
		cmd = get_cmd();
		if (!cmd)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			clear_all(&shell);
			exit (shell.status);
		}
		parser(cmd, shell.env);
		shell.cmd_list_head = shell.cmd_list;
		exec(shell.cmd_list);
		clean_cmd_list(shell.cmd_list_head);
		memclean(shell.env, len_2d_str(shell.env));
		shell.env = collect_env(shell.env_list);
	}
	return (0);
}
