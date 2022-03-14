# include "minishell.h"

void cmd_split(t_cmd *cmd, char *str, char **envp)
{
	int i;
	char ch;

	i = -1;
	(void)envp;
	(void)cmd;
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
			str = pipe_parse(i, str, envp);
			printf("%s str_tr\n", str);
			i = 0;
		}
	}
}

void	*parser(t_cmd *cmd, char *str, char **envp)
{
	if (!prepars(str))
		ft_putendl_fd("Error", 1);
	else
	{
		cmd_split(cmd, str, envp);
	}
	return NULL;
}