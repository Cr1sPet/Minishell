# include "minishell.h"

int prepars(char *line, int i)
{
	char	ch;

	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			ch = line[i];
			i++;
			while (line[i] && line[i] != ch)
				i++;
			if (!line[i] || line[i] != ch)
				return (0);
		}
	}
	return (1);
}

char *parser(t_cmd pars_cmd,char *str, char **envp)
{
	int i;
	char *cmd;

	i = -1;
	if (!prepars(str, i))
		return "Error";
	while (str[++i] != ' ')
		;
	cmd = malloc(sizeof(char) *  i);
	cmd = ft_substr(str, 0, i);
	pars_cmd.args[0] = cmd;
	free(cmd);
	i = -1;
	while (str[++i])
	{  
		if (str[i] == '\'')
			str = ft_quotes(str, &i);
		if (str[i] == '"')
			str = ft_quotes_2(str, &i, envp);
        if (str[i] == '$')
			str = ft_dollar(str, &i, envp);
	}
	pars_cmd.args[2] = str;
	free(str);
	return (pars_cmd.args[2]);
}