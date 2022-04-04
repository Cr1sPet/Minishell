/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:05:29 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:05:30 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_work(char **args, int len)
{
	int	j;

	j = 1;
	if (!strcmp(args[1], "-n"))
		j++;
	while (args[j])
	{
		ft_putstr_fd(args[j], STDOUT_FILENO);
		if (j++ < len - 1)
			write(STDOUT_FILENO, " ", STDOUT_FILENO);
	}
}

void	echo(char **args)
{
	int	len;

	len = 0;
	shell.status = 0;
	while (args[len])
		len++;
	if (1 == len)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (len >= 2)
		echo_work(args, len);
	if (strcmp(args[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
}
