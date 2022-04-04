/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:13:29 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:13:29 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **args)
{
	char	*pwd;
	char	buf[4096];

	pwd = getcwd(buf, sizeof(buf));
	if (pwd && args)
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		shell.status = 0;
	}
	else
	{
		perror("minishell: pwd: ");
		shell.status = 127;
	}
}
