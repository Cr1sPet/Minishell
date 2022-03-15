# include "minishell.h"

void cmd_split(char *str, char **envp)
{
	int i;
	char ch;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			while (str[++i] && str[i] != ch)
				;
		}
		if (str[i] == '|')
			str = pipe_parse(&i, str, envp);
		if (str[i] == '>')
			str = right_redirect(str, &i);
		if (str[i] == '<')
			left_redirect();
	}
	str = pipe_parse(&i, str, envp);
}

void	*parser(char *str, char **envp)
{
	if (!prepars(str) || str[0] == '|')
		ft_putendl_fd("Error", 1);
	else
		cmd_split(str, envp);
	return NULL;
}