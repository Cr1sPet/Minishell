# include "minishell.h"

int	prepars(const char *str)
{
	char	ch;
	int		i;

	i = 0;
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
	return (1);
}

char	*ft_space(char *str, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = i;
	while (str[i] == ' ')
		++i;
	tmp = ft_substr(str, 0, j + 1);
	tmp2 = ft_strdup(str + i);
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	free(str);
	return (tmp);
}

char	*correct_str(char *str, char **envp)
{
	int		i;

	i = -1;
	str = ft_strtrim(str, " ");
	while (str[++i])
	{
		if (str[i] == ' ')
			str = ft_space(str, i);
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
	if (!prepars(str))
		ft_putendl_fd("Error", 1);
	else
	{
		str = correct_str(str, envp);
		printf("%s<--str\n", str);
		list_cmd(cmd, str);
	}
	free(str);
	return NULL;
}