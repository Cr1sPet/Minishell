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

char *ft_gap2(char *str, int *i)
{
	int j;
	char *tmp;
	char *tmp2;
	char *tmp3;

	j = *i;
	while (str[(*i)])
	{
		if (str[(*i)] == '$')
			printf("check");
		if (str[(*i)] == '"')
			break;
		(*i)++;
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

int ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return 1;
	return 0;
}

char *ft_dollar(char *str, int *i, char **envp)
{
	char *tmp;
	char *tmp2;
	// char *tmp3;
	int j;
	int k;

	j = *i;
	k = -1;
	while (str[++(*i)])
	{
		if (!ifkey(str[*i]))
			break;
	}
	if (*i == j + 1)
		return (str);
	tmp = ft_substr(str, j + 1, *i - j  - 1);
	int z = 0;
	while (envp[++k])
	{
		if (ft_strnstr(envp[k], tmp, ft_strlen(tmp)))
		{
			while (envp[k][z] && envp[k][z] != '=')
				z++;
			tmp2 = ft_substr(envp[k], 0, z);
			if (ft_strncmp(tmp,tmp2,ft_strlen(tmp)) == 0)
				break;
		}
	}
	tmp2 = ft_substr(envp[k], z + 1, ft_strlen(envp[k]) - z);
	// printf("%s\n", tmp2);
	return tmp;
}



void parse(char *str, char **envp)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'') // '
			str = ft_gap(str, &i);
		if (str[i] == '"') // ""
			str = ft_gap2(str, &i);
        if (str[i] == '$') // $
			str = ft_dollar(str, &i, envp);
	}
	printf("%s\n", str);
}