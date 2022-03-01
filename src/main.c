# include "minishell.h"

char	*get_cmd()
{
	char  *str;

	str = readline("minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mshell;
	t_cmd		*temp_cmd;
	initialisation (&mshell, envp);
	
	mshell.cmd_list->args = (char **) malloc (sizeof(char *) * 2);
	mshell.cmd_list->args[0] = ft_strdup("meg");
	mshell.cmd_list->args[1] = NULL;
	mshell.cmd_list->pipe_out =pipe_out;
	mshell.cmd_list->pipe_in = default_pipe_in;
	mshell.cmd_list->redir_in = default_redir_in;
	mshell.cmd_list->redir_out = default_redir_out;

	lst_cmdadd_back(&mshell.cmd_list, lst_cmdnew(&mshell));
	temp_cmd = mshell.cmd_list;
	mshell.cmd_list = mshell.cmd_list->next;
	mshell.cmd_list->args = (char **) malloc (sizeof(char *) * 2);
	mshell.cmd_list->args[0] = ft_strdup("/bin/cat");
	mshell.cmd_list->args[1] = NULL;
	mshell.cmd_list->pipe_in = pipe_in;
	mshell.cmd_list->pipe_out = default_pipe_out;
	mshell.cmd_list->redir_in = default_redir_in;
	mshell.cmd_list->redir_out = default_redir_out;
	if (-1 == pipe(mshell.fds))
	{
		ft_putendl_fd("ERROR WITH PIPE", mshell.stdout);
		exit (1);
	}
	// cmd_list.f1 = open ("in.txt", O_RDONLY);
	// if (-1 == cmd_list.f1)
	// {
		// puts("ERROR IN FILE OPEN");
		// exit (1);
	// }
	// printf("%s\n", mshell.cmd_list->args[0]);
	// mshell.cmd_list->f2 = open ("out.txt", O_APPEND | O_CREAT | O_RDWR, 0644);
	// if (-1 == mshell.cmd_list->f2)
	// {
		// puts("ERROR IN FILE OPEN");
		// exit (1);
	// }
	mshell.cmd_list = temp_cmd;
	exec(&mshell);
	return (0);
}
