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
	t_minishell		mshell;
	t_cmd			*temp_cmd;

	initialisation(&mshell, envp);
	mshell.cmd_list->args = (char **) malloc (sizeof(char *) * 3);
	mshell.cmd_list->args[0] = ft_strdup("cat");
	mshell.cmd_list->args[1] = ft_strdup("fegg.c");
	mshell.cmd_list->args[2] = NULL;
	mshell.cmd_list->pipe_in = default_pipe_in;
	mshell.cmd_list->pipe_out = default_pipe_out;
	mshell.cmd_list->redir_in = default_redir_in;
	mshell.cmd_list->redir_out = default_redir_out;
	mshell.cmd_list->next = NULL;
	exec(mshell.cmd_list);
	return (0);
}
