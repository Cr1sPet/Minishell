# include "minishell.h"

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
	char	*cmd;
	t_cmd	*str_cmd;

	(void)argv;
	str_cmd = malloc(sizeof(t_cmd));
	if (1 != argc)
		return (1);
	while (1)
	{
		cmd = get_cmd();
		parser(str_cmd, cmd, envp);
		if (str_cmd->args[0])
			puts(str_cmd->args[0]);
	}
	return (0);
}