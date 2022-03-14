# include "minishell.h"

char	*get_cmds(char *str, int *i, int j)
{
	char	ch;

	ch = str[(*i)];
	while (str[++(*i)] && str[(*i)] != ch)
		;
	return (ft_substr(str, j, *i - j + 1));
}

char	**command_split(char *str)
{
	char	**cmds;
    int     h;
    int     i; 
    int     j;

    i = -1;
    j = 0;
    h = 0;
	cmds = ft_calloc(sizeof(char *), 100);
	while (str[++i])
	{
		j = i;
        while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
            i++;
		if ((str[i] == ' ' || str[i] == '\0') && j != i)
		{
			cmds[h++] = ft_substr(str, j, i - j);
			if (str[i] == '\0')
				break ;
		}
		if (str[i] == '\'' || str[i] == '\"')
			cmds[h++] = get_cmds(str, &i, j);
	}
	free(str);
	return (cmds);
}

char *pipe_parse(int i,char *str, char **envp) 
{
    char    *temp;
    char    *ret;
    char    **cmd;

    (void)envp;
    temp = ft_substr(str, 0, i);
    cmd = command_split(temp);
    ret =  ft_substr(str, i, ft_strlen(str));
    int k;

    k = -1;
    while (cmd[++k])
    {
        cmd[k] = correct_str(cmd[k], envp);
        printf("%s\n", cmd[k]);
    }
        
    return ret;
}