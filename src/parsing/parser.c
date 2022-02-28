# include "minishell.h"

char *parse(char *str, char **envp)
{
	int i;

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
	return (str);
}