# include "minishell.h"

char *get_cmd()
{
	char  *str;

	str = readline("minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

int main(int argc, char **argv, char **envp)
{
	char		*cmd;
	t_minishell	mshell;

	(void)argc;
	(void)argv;
	if (1 != argc)
		return (1);
	initialisation (&mshell, envp);
	int	i = 0;
	while (mshell.env[i])
		puts(mshell.env[i++]);
	while (1)
	{
		cmd = get_cmd ();
		// exec(cmd, );
	}
	return (0);
}