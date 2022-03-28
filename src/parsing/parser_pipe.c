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
    char    ch;
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
        if (str[i] == '>' || str[i] == '<')
        {
            ch = str[i];
            if (str[i + 1] == ch)
            {
                cmds[h++] = ft_substr(str, j, 2);
                i++;
            }
            else
                cmds[h++] = ft_substr(str, j, 1);       
        }
        else 
        {
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

	}
	free(str);
	return (cmds);
}

int check_redir(char *str, int i)
{
    int j;
    char ch;

    j = -1;
    if (str[0] == '>' ||  str[0] == '<')
        return 1;
    while(++j < i)
    {
        if (str[j] == '\'' || str[j] == '\"')
		{
			ch = str[j];
			while (str[++j] && str[j] != ch)
				;
		}
        if (str[j] == '>' ||  str[j] == '<')
            return j;
    }
    return 0;
}

char *helper(char *str)
{
    char *ret;
    int j;
    int i;

    j = -1;
    while (str[++j] == '<' || str[j] == '>' || str[j] == ' ')
        ;
    i = j;
    while (str[i] && str[i] != ' ')
        i++; 
    ret =  ft_substr(str, 0, i);
    ret = ft_strtrim(ret, " ");
    return ret;
}

char	*pipe_parse(int *i,char *str, char **envp)
{
    char    *temp;
    char    *ret;
    char    **temp_cmd;
    char    **cmd;
    int j;
    int k;

    j = 0;
    k = 0;
    temp = ft_substr(str, 0, *i);
    temp_cmd = command_split(temp);
    temp_cmd = correct_str(temp_cmd,envp);
    cmd = ft_calloc(sizeof(char *), 100);
    while(temp_cmd[j])
    {
        if ((ft_strncmp(temp_cmd[j], ">", 1) == 0 && ft_strlen(temp_cmd[j]) == 1) || (ft_strncmp(temp_cmd[j], ">>", 2) == 0 && ft_strlen(temp_cmd[j]) == 2) || (ft_strncmp(temp_cmd[j], "<", 1) == 0 && ft_strlen(temp_cmd[j]) == 1) || (ft_strncmp(temp_cmd[j], "<<", 2) == 0 && ft_strlen(temp_cmd[j]) == 2))
                j++;
        else
        {
            cmd[k] = ft_strdup(temp_cmd[j]);
            k++;
        }
        j++; 
    }
    cmd[k] = NULL;
    ret =  ft_substr(str, *i + 1, ft_strlen(str));
    ft_lstadd_back_parse(&shell.cmd_list, ft_lstnew_parse(cmd));
    if (check_redir(str, *i))
        redir(temp_cmd);
    j  = 0;
    while (temp_cmd[j])
    {
        free(temp_cmd[j]);
        j++;
    }
    free(temp_cmd);
    *i = 0;
    return ret;
}


// char	*pipe_parse(int *i,char *str, char **envp)
// {
//     char    *temp;
//     char    *temp_2;
//     char    *ret;
//     char    **cmd;

//     temp = ft_substr(str, 0, *i);
//     if (check_redir(str, *i))
//     {
//         temp = ft_substr(str, 0, check_redir(str, *i));
//         temp_2 = ft_substr(str,  check_redir(str, *i), ft_strlen(str) - check_redir(str, *i));
//     }
//     cmd = command_split(temp);
//     cmd = correct_str(cmd,envp);
//     ret =  ft_substr(str, *i + 1, ft_strlen(str));
//     ft_lstadd_back_parse(&shell.cmd_list, ft_lstnew_parse(cmd));
//     if (check_redir(str, *i))
//         redir(temp_2, envp);
//     *i = 0;
//     return ret;
// }