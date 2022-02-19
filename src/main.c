# include "minishell.h"

char *get_cmd()
{
	char  *str;

	str = readline("minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd		cmd_list;
	t_minishell	mshell;

	initialisation (&mshell, envp);
	cmd_list.mshell = &mshell;
	cmd_list.limiter = "limiter";
	cmd_list.args = (char **) malloc (sizeof(char *) * 2);
	cmd_list.args[0] = strdup("/bin/cat");
	// cmd_list.args[1] = strdup("-e");
	cmd_list.args[1] = NULL;
	// cmd_list.redir_in = 0;
	// cmd_list.redir_out = 0;
	cmd_list.pipe_in = 0;
	cmd_list.pipe_out = pipe_out;
	cmd_list.redir_in = redir_in_1;
	cmd_list.redir_out = redir_out_1;
	cmd_list.f1 = open ("test", O_RDONLY);
	if (-1 == cmd_list.f1)
	{
		puts("ERROR IN FILE OPEN");
		exit (1);
	}
	cmd_list.f2 = open ("out.txt", O_APPEND | O_CREAT | O_RDWR, 0644);
	if (-1 == cmd_list.f2)
	{
		puts("ERROR IN FILE OPEN");
		exit (1);
	}
	exec(&cmd_list);
	puts("\nHELLO");
	return (0);
}
