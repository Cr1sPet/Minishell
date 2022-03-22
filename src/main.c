# include "minishell.h"

char	*get_cmd()
{
	char	*str;

	str = readline("🦍 minishell > ");
	if (str && *str)
		add_history (str);
	return (str);
}

t_cmd	*custom_cmd(char **args, t_redir *redir_in, t_redir *redir_out, int pipe_in, int pipe_out)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = args;
	cmd->redir_in = redir_in;
	cmd->redir_out = redir_out;
	cmd->pipe_in = pipe_in;
	cmd->pipe_out = pipe_out;
	cmd->next = NULL;
	return (cmd);
}

int	main(int argc, char **argv, char **envp) {
	(void) argv;
	if (1 != argc)
		return (1);
	initialisation(envp);
	t_redir * red = NULL;
	lst_rediradd_back(&red, lst_redirnew("test_files/1", redir_in_1));
	lst_rediradd_back(&red, lst_redirnew("test_files/2", redir_in_1));
	lst_rediradd_back(&red, lst_redirnew("test_files/3", redir_in_1));
	t_redir * red1 = NULL;
	lst_rediradd_back(&red1, lst_redirnew("test_files/4", redir_out_1));
	lst_rediradd_back(&red1, lst_redirnew("test_files/5", redir_out_1));
	lst_rediradd_back(&red1, lst_redirnew("test_files/6", redir_out_2));
	lst_cmdadd_back(&shell.cmd_list, custom_cmd(ft_split("cat -e", ' '),
			red, red1, default_pipe_in, default_pipe_out));
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

