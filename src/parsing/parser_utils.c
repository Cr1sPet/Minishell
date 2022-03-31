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

char	*correct_str(char *str, char **envp)
{
	int		i;
	int		ok;

	i = -1;
	ok = 0;
    while (str[++i]) 
    {
		if (str[i] == '\"' && !ok)
		{
			i++;
			ok += 1;
		}
		if (str[i] == '\"' && ok)
			ok--;
		if (str[i] == '\'' && ok != 1)
		{
			while (str[++i] && str[i] != '\'')
					;
		}
		if (str[i] == '$')
			str = ft_dollar(str, &i, envp);
    }	
	return (str);
}

void error_parser(char *cmd)
{
	ft_putendl_fd(cmd, 2);
	clean_cmd_list();
}