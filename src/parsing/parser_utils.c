/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 21:50:56 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 18:48:27 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (str[i] == '|')
		{
			while (str[++i] && str[i] == ' ')
				;
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
				return (0);
		}
	}
	return (1);
}

char	*correct_str(char *str, char **envp, int i, int ok)
{
	char	*temp;
	char	*temp_2;

	temp = ft_strdup(str);
	free(str);
	while (temp[++i])
	{
		if (temp[i] == '\"' && !ok)
		{
			i++;
			ok += 1;
		}
		if (temp[i] == '\"' && ok)
			ok--;
		if (temp[i] == '\'' && ok != 1)
			while (temp[++i] && temp[i] != '\'')
				;
		if ('$' == temp[i])
		{
			temp_2 = ft_strdup(temp);
			free(temp);
			temp = ft_dollar(temp_2, &(i), shell.env);
		}
	}
	return (temp);
}

int	error_parser(char *cmd)
{
	ft_putendl_fd(cmd, 2);
	clean_cmd_list(shell.cmd_list);
	shell.cmd_list = NULL;
	return (-1);
}
