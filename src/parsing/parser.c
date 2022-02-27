# include "minishell.h"

char *ft_gap(char *str, int *i)
{
	int j;
	char *tmp;
	char *tmp2;
	char *tmp3;

	j = *i;
	while (str[++(*i)])
	{
		if (str[(*i)] == '\'')
			break;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp3);
	free(str);
	return tmp;
}

char *ft_gap2(char *str, int *i, char **envp)
{
	int j;
	char *tmp;
	char *tmp2;
	char *tmp3;
	// char *tmp4;

	j = *i;
	while (str[++(*i)])
	{
		if (str[(*i)] == '$')
		{
			str = ft_dollar(str, i, envp);
		}
		if (str[(*i)] == '\"')
			break;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	free(str);
	return tmp;
}

char *parse(char *str, char **envp)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'') // '
			str = ft_gap(str, &i);
		if (str[i] == '"') // ""
			str = ft_gap2(str, &i, envp);
        if (str[i] == '$') // $
			str = ft_dollar(str, &i, envp);
	}
	return (str);
}