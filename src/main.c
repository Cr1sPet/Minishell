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
	temp_cmd = mshell.cmd_list;
	mshell.cmd_list->args = (char **) malloc (sizeof(char *) * 3);
	mshell.cmd_list->args[0] = ft_strdup("echo");
	mshell.cmd_list->args[1] = ft_strdup("head");
	// mshell.cmd_list->args[2] = ft_strdup("-n");
	mshell.cmd_list->args[2] = NULL;
	mshell.cmd_list->pipe_in = default_pipe_in;
	mshell.cmd_list->pipe_out = pipe_out;
	mshell.cmd_list->redir_in = default_redir_in;
	mshell.cmd_list->redir_out = default_redir_out;

	lst_cmdadd_back(&mshell.cmd_list, lst_cmdnew(&mshell));
	temp_cmd = temp_cmd->next;
	temp_cmd->args = (char **) malloc (sizeof(char *) * 3);
	temp_cmd->args[0] = ft_strdup("cat");
	temp_cmd->args[1] = ft_strdup("-e");
	temp_cmd->args[2] = NULL;
	temp_cmd->pipe_in = pipe_in;
	temp_cmd->pipe_out = pipe_out;
	temp_cmd->redir_in = default_redir_in;
	temp_cmd->redir_out = default_redir_out;
	temp_cmd->next = NULL;

	lst_cmdadd_back(&mshell.cmd_list, lst_cmdnew(&mshell));
	temp_cmd = temp_cmd->next;
	temp_cmd->args = (char **) malloc (sizeof(char *) * 3);
	temp_cmd->args[0] = ft_strdup("wc");
	temp_cmd->args[1] = ft_strdup("-l");
	temp_cmd->args[2] = NULL;
	temp_cmd->pipe_in = pipe_in;
	temp_cmd->pipe_out = default_pipe_out;
	temp_cmd->redir_in = default_redir_in;
	temp_cmd->redir_out = default_redir_out;
	temp_cmd->next = NULL;
	exec(mshell.cmd_list);
	return (0);
}
