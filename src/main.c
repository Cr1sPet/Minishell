# include "minishell.h"

char *get_cmd()
{
	char  *str;

	str = readline("🦍 minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*cmd;
	t_cmd pars_cmd;

	if (1 != argc)
		return (1);
	while (1)
	{
		cmd = get_cmd();
		cmd = parser(pars_cmd,cmd, envp);
		puts(cmd);
	}
	return (0);
}