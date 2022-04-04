/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:59:35 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:41:08 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*change_dollar(char *str)
{
	int		i;
	char	*temp;
	char	*save;

	i = -1;
	save = ft_strdup(str);
	while (str[++i])
	{
		if ('$' == str[i])
		{
			temp = ft_dollar(str, &(i), g_shell.env);
			if (!temp)
				return (NULL);
			if (!ft_strcmp(save, temp))
			{
				free(save);
				return (temp);
			}
			str = temp;
		}
	}
	free(save);
	return (str);
}

int	work_here_doc(char *limiter, int *f)
{
	char	*str;

	signal_init_here();
	while (1)
	{
		str = readline("> ");
		if (str && *str)
			add_history(str);
		if (!ft_strcmp(str, limiter))
			break ;
		str = change_dollar(str);
		if (!str)
			return (-1);
		ft_putendl_fd(str, f[1]);
		free (str);
	}
	close (f[0]);
	close (f[1]);
	return (1);
}
