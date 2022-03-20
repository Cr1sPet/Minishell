# include "minishell.h"

char	*get_cmd()
{
	char	*str;

	str = readline("🦍 minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

//<<<<<<< HEAD
int	main(int argc, char **argv, char **envp) {
	char *cmd;   
	t_cmd *temp_cmd;
	(void) argv;
	if (1 != argc)
		return (1);
	
	initialisation(envp);

	shell.cmd_list = NULL;
	lst_cmdadd_back(&shell.cmd_list, lst_cmdnew(&shell));
	temp_cmd = shell.cmd_list;
	shell.cmd_list->args = (char **) malloc (sizeof(char *) * 3);
	shell.cmd_list->args[0] = ft_strdup("echo");
	shell.cmd_list->args[1] = ft_strdup("hello");
	// mshell.cmd_list->args[2] = ft_strdup("-n");
	shell.cmd_list->args[2] = NULL;
	shell.cmd_list->pipe_in = default_pipe_in;
	shell.cmd_list->pipe_out = pipe_out;
	shell.cmd_list->redir_in = default_redir_in;
	shell.cmd_list->redir_out = default_redir_out;
	lst_cmdadd_back(&shell.cmd_list, lst_cmdnew(&shell));
	temp_cmd = temp_cmd->next;
	temp_cmd->args = (char **) malloc (sizeof(char *) * 3);
	temp_cmd->args[0] = ft_strdup("cat");
	temp_cmd->args[1] = ft_strdup("-e");
	// mshell.cmd_list->args[2] = ft_strdup("-n");
	temp_cmd->args[2] = NULL;
	temp_cmd->pipe_in = pipe_in;
	temp_cmd->pipe_out = default_pipe_out;
	temp_cmd->redir_in = default_redir_in;
	temp_cmd->redir_out = default_redir_out;
	exec();
	return 0;
}
//=======ddfdf
//
//
//int	main(int argc, char **argv, char **envp)
//{
//	t_minishell		mshell;
//	t_cmd			*temp_cmd;
//

//	// temp_cmd = mshell.cmd_list;
//	mshell.cmd_list->args = (char **) malloc (sizeof(char *) * 3);
//	mshell.cmd_list->args[0] = ft_strdup("export");
//	mshell.cmd_list->args[1] = ft_strdup("AAAAAAAAAAAAAA=WWOWOOWOW");
//	// mshell.cmd_list->args[2] = ft_strdup("-n");
//	mshell.cmd_list->args[2] = NULL;
//	mshell.cmd_list->pipe_in = default_pipe_in;
//	mshell.cmd_list->pipe_out = pipe_out;
//	mshell.cmd_list->redir_in = default_redir_in;
//	mshell.cmd_list->redir_out = default_redir_out;
//
//	// lst_cmdadd_back(&mshell.cmd_list, lst_cmdnew(&mshell));
//	// temp_cmd = temp_cmd->next;
//	char	**args;
//	args = (char **) malloc (sizeof(char *) * 3);
//	args[0] = ft_strdup("export");
//	args[1] = ft_strdup("ZZZ=BAZUKA");
//	args[2] = NULL;
//
//	char	**args1;
//	args1 = (char **) malloc (sizeof(char *) * 3);
//	args1[0] = ft_strdup("export");
//	args1[1] = ft_strdup("AAAAAAAAAAAAAA");
//	args1[2] = NULL;
//	// pipe_in = pipe_in;
//	// pipe_out = pipe_out;
//	// redir_in = default_redir_in;
//	// redir_out = default_redir_out;
//	// next = NULL;
//
//	// lst_cmdadd_back(&mshell.cmd_list, lst_cmdnew(&mshell));
//	// temp_cmd = temp_cmd->next;
//	// temp_cmd->args = (char **) malloc (sizeof(char *) * 3);
//	// temp_cmd->args[0] = ft_strdup("wc");
//	// temp_cmd->args[1] = ft_strdup("-l");
//	// temp_cmd->args[2] = NULL;
//	// temp_cmd->pipe_in = pipe_in;
//	// temp_cmd->pipe_out = default_pipe_out;
//	// temp_cmd->redir_in = default_redir_in;
//	// temp_cmd->redir_out = default_redir_out;
//	// temp_cmd->next = NULL;
//	// exec(mshell.cmd_list);
//	// print_env_store(mshell.env_store, &mshell);
//	// ft_putendl_fd("============================================================", 1);
//	// char * a = mshell.export[0].key;
//	// print_env_store(mshell.export, &mshell);
//	// export(mshell.cmd_list->args, &mshell);
//	// print_env_store(mshell.export, &mshell);
//	export(args, &mshell);
//	// print_env_store(mshell.export, &mshell);
//	// print_env_store(mshell.env_store, &mshell);
//	char **al = collect_env(&mshell);
//	while (*al)
//	{
//		ft_putendl_fd(*al, 1);
//		al ++;
//>>>>>>> crs
//	}
//	return (0);
//}