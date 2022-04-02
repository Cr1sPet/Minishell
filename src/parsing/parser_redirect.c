/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 21:18:27 by spurple           #+#    #+#             */
/*   Updated: 2022/04/01 21:30:08 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// void	add_redir_list(char **cmd, int i, t_redir *redir, int type)
// {
// 	if (!cmd[i + 1])
// 		error_parser("Syntax Error");
// 	else
// 		ft_lstadd_back_redir(&redir, ft_lstnew_redir(ft_strdup(cmd[i + 1]), \
// 		type));
// }

// void	redir(char **cmd, int i)
// {
// 	while (cmd[++i])
// 	{
// 		if (ft_strncmp(cmd[i], "<<", 2) == 0 && ft_strlen(cmd[i]) == 2)
// 			add_redir_list(cmd, i, ft_lstlast_parse(shell.cmd_list)->redir_in, \
// 			redir_in_2);
// 		else if (ft_strncmp(cmd[i], ">>", 2) == 0 && ft_strlen(cmd[i]) == 2)
// 			add_redir_list(cmd, i, &ft_lstlast_parse(shell.cmd_list)-> \
// 			redir_out, redir_out_2);
// 		else if (ft_strncmp(cmd[i], ">", 1) == 0 && ft_strlen(cmd[i]) == 1)
// 			add_redir_list(cmd, i, &ft_lstlast_parse(shell.cmd_list)-> \
// 			redir_out, redir_out_1);
// 		else if (ft_strncmp(cmd[i], "<", 1) == 0 && ft_strlen(cmd[i]) == 1)
// 			add_redir_list(cmd, i, &ft_lstlast_parse(shell.cmd_list)-> \
// 			redir_in, redir_in_1);
// 	}
// }


int	redir(char **cmd, int i)
{
	while(cmd[++i])
    {
        if (ft_strncmp(cmd[i], "<<", 2) == 0 && ft_strlen(cmd[i]) == 2)
        {
            if (!cmd[i + 1])
                return (error_parser("Syntax Error"));
            ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redir_in, ft_lstnew_redir(ft_strdup(cmd[i + 1]), redir_in_2));
        }
        else if (ft_strncmp(cmd[i], ">>", 2) == 0 && ft_strlen(cmd[i]) == 2)
        {
            if (!cmd[i + 1])
                return (error_parser("Syntax Error"));
            ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redir_out, ft_lstnew_redir(ft_strdup(cmd[i + 1]), redir_out_2));
        }
        else if (ft_strncmp(cmd[i], ">", 1) == 0 && ft_strlen(cmd[i]) == 1)
        {
            if (!cmd[i + 1])
                return (error_parser("Syntax Error"));
            ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redir_out, ft_lstnew_redir(ft_strdup(cmd[i + 1]), redir_out_1));
        }
        else if (ft_strncmp(cmd[i], "<", 1) == 0 && ft_strlen(cmd[i]) == 1)
        {
            if (!cmd[i + 1])
                return (error_parser("Syntax Error"));
            ft_lstadd_back_redir(&ft_lstlast_parse(shell.cmd_list)->redir_in, ft_lstnew_redir(ft_strdup(cmd[i + 1]), redir_in_1));
        }
    }
	return 1;
}
