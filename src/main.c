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
	shell.cmd_list->args[1] = ft_strdup("$?");
	// mshell.cmd_list->args[2] = ft_strdup("-n");
	shell.cmd_list->args[2] = NULL;
	shell.cmd_list->pipe_in = default_pipe_in;
	shell.cmd_list->pipe_out = default_pipe_out;
	shell.cmd_list->redir_in = default_redir_in;
	shell.cmd_list->redir_out = default_redir_out;
	shell.cmd_list->next = NULL;
	lst_cmdadd_back(&shell.cmd_list, lst_cmdnew(&shell));
	temp_cmd = temp_cmd->next;
	temp_cmd->args = (char **) malloc (sizeof(char *) * 3);
	temp_cmd->args[0] = ft_strdup("wc");
	temp_cmd->args[1] = ft_strdup("-l");
	// mshell.cmd_list->args[2] = ft_strdup("-n");
	temp_cmd->args[2] = NULL;
	temp_cmd->pipe_in = pipe_in;
	temp_cmd->pipe_out = pipe_out;
	temp_cmd->redir_in = default_redir_in;
	temp_cmd->redir_out = default_redir_out;
	temp_cmd->next = NULL;
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
	temp_cmd->next = NULL;
	exec();
	return (0);
}
// int	main(int argc, char **argv, char **envp) {
// 	char *cmd;   

// 	(void) argv;
// 	if (1 != argc)
// 		return (1);
// 	signal_init();
// 	while (1) {
// 		cmd = get_cmd();
// 		// cmd = ft_strdup("echo hello");
// 		parser(cmd, envp);
// 		initialisation(envp);
// 		// if (str_cmd->args[0])
// 		// 	puts(str_cmd->args[0]);
// 		// echo(shell.cmd_list->args);
// 		// ft_putstr_fd(*shell.cmd_list->mshell->env, 1);
// 		exec(shell.cmd_list);
// 		// shell.cmd_list = shell.cmd_list->next;
// 	}
// 	return 0;
// }
