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

int check_redir(char *str, int i)
{
    int j;

    j = -1;
    while(++j < i)
    {
        if (str[j] == '>' ||  str[j] == '<')
            return j;
    }
    return 0;
}

char *pipe_parse(int *i,char *str, char **envp) 
{
    char    *temp;
    char    *temp_2;
    char    *ret;
    char    **cmd;

    temp = ft_substr(str, 0, *i);
    if (check_redir(str, *i))
    {
        temp = ft_substr(str, 0, check_redir(str, *i));
        temp_2 = ft_substr(str,  check_redir(str, *i), ft_strlen(str) - check_redir(str, *i));
    }
    cmd = command_split(temp);
    cmd = correct_str(cmd,envp);
    ret =  ft_substr(str, *i + 1, ft_strlen(str));
    ft_lstadd_back_parse(&shell.cmd_list, ft_lstnew_parse(cmd));
    if (check_redir(str, *i))
        redir(temp_2, envp);
    *i = 0;
    free(temp);
    free(str);
    return ret;
}