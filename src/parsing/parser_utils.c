# include "minishell.h"

int	prepars(const char *str)
{
	char	ch;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			i++;
			while (str[i] && str[i] != ch)
				i++;
			if (!str[i] || str[i] != ch)
				return (0);
		}
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
        {
			while (str[++i] && str[i] == ' ')
                    ;
            if (str[i + 1] == ' ' || str[i + 1] == '\0')
                return (0);
        }
	}

	return (1);
}

char	**correct_str(char **str, char **envp)
{
	int		i;
    int     j;

	i = -1;
	while (str[++i])
	{
        j = -1;
        while (str[i][++j]) 
        {
            if (str[i][j] == '\'')
			    str[i] = ft_quotes(str[i], &j);
		    if (str[i][j] == '\"')
			    str[i] = ft_quotes_2(str[i], &j, envp);
		    if (str[i][j] == '$')
			    str[i] = ft_dollar(str[i], &j, envp);
        }
	}
	return (str);
}