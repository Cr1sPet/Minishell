# include "minishell.h"

//void	parse_error(char *str)
//{
//	printf("Error\n");
//	return (NULL);
//}

// char	*ft_space(char *str, int i)
// {
// 	char	*tmp;
// 	char	*tmp2;
// 	int		j;

// 	j = i;
// 	while (str[i] == ' ')
// 		++i;
// 	tmp = ft_substr(str, 0, j + 1);
// 	tmp2 = ft_strdup(str + i);
// 	tmp = ft_strjoin(tmp, tmp2);
// 	free(tmp2);
// 	free(str);
// 	return (tmp);
// }

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
	return (1);
}

char	*correct_str(char *str, char **envp)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = ft_quotes(str, &i);
		if (str[i] == '\"')
			str = ft_quotes_2(str, &i, envp);
		if (str[i] == '$')
			str = ft_dollar(str, &i, envp);
	}
	return (str);
}