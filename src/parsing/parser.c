# include "minishell.h"

int	prepars(const char *line, int i)
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

char	*ft_space(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = *i;
	while (str[(*i)] == ' ')
		++(*i);
	tmp = ft_substr(str, 0, j + 1);
	tmp2 = ft_strdup(str + *i);
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	free(str);
	return (tmp);
}

char	*correct_str( char *str, char **envp)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			str = ft_space(str, &i);
		if (str[i] == '\'')
			str = ft_quotes(str, &i);
		if (str[i] == '\"')
			str = ft_quotes_2(str, &i, envp);
		if (str[i] == '$')
			str = ft_dollar(str, &i, envp);
	}
	return (str);
}

void	list_cmd(t_cmd *cmd, char *str)
{
	cmd->args = ft_split(str, ' ');
}

void	*parser(t_cmd *cmd, char *str, char **envp)
{
	if (!prepars(str, -1))
	{
		ft_putendl_fd("Error", 1);
		return NULL;
	}
	str = correct_str(str, envp);
	list_cmd(cmd, str);
	printf("%s <--str\n", str);
	free(str);
	return NULL;
}