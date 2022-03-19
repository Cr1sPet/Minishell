# include "minishell.h"

void	cmd_split(char *str, char **envp)
{
	int		i;
	char	ch;
	int		k;

	i = -1;
	k = 0;
	(void)envp;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			while (str[++i] && str[i] != ch)
				;
		}
		if (str[i] == '|')
		{
			k++;
			str = pipe_parse(&i, str, envp);
			shell.cmd_list->pipe_out = pipe_out;
			if (k > 1)
				shell.cmd_list->pipe_in = pipe_in;
		}
	}
	pipe_parse(&i, str, envp);
	shell.cmd_list->pipe_in = pipe_in;
}

void	*parser(char *str, char **envp)
{
	if (str && str[0] == '\0')
		return NULL;
	if (!prepars(str) || str[0] == '|')
		ft_putendl_fd("Error", 1);
	else
	{
		cmd_split(str, envp);

	}
		

	// free(str);
//	while (shell.cmd_list)
//   {
//       int i = -1;
//       while (shell.cmd_list->args[++i])
//		{
//			printf("%s \n", shell.cmd_list->args[i]);
//			// free(shell.cmd_list->args[i]);
//		}
//		while (shell.cmd_list->redr_list)
//		{
//			printf("%s<struct\n", shell.cmd_list->redr_list->filename);
//			printf("%d   %d<type\n", shell.cmd_list->redr_list->type_redr, shell.cmd_list->redr_list->double_redir);
//			// free(shell.cmd_list->redr_list->filename);
//			shell.cmd_list->redr_list= shell.cmd_list->redr_list->next;
//		}
//       printf("--------------------------------------\n");
//       shell.cmd_list = shell.cmd_list->next;
//   }
	return NULL;
}