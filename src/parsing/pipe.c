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
    cmd = correct_str(cmd,envp);
    ret =  ft_substr(str, i + 1, ft_strlen(str));
    ft_lstadd_back_parse(&shell.cmd_list, ft_lstnew_parse(cmd));
    while (shell.cmd_list)
    {
        int i = -1;
        while (shell.cmd_list->args[++i])
            printf("%s \n", shell.cmd_list->args[i]);
        printf("--------------------------------------\n");
        shell.cmd_list = shell.cmd_list->next;
    }
    return ret;
}