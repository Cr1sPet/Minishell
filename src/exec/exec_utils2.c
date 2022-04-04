/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spurple <spurple@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:59:26 by spurple           #+#    #+#             */
/*   Updated: 2022/04/04 19:41:59 by spurple          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int	**fds)
{
	int	i;

	i = 0;
	if (fds)
	{
		while (fds[i])
		{
			close(fds[i][0]);
			close(fds[i][1]);
			i++;
		}
	}
}

void	wait_pids(pid_t	*pids, int nmb)
{
	int	i;
	int	status;

	i = 0;
	status = g_shell.status;
	if (pids)
	{
		while (i < nmb)
		{
			waitpid(pids[i], &status, 0);
			i++;
		}
		if (g_shell.status != status)
			g_shell.status = WEXITSTATUS(status);
		free(pids);
	}
}

void	cmd_end_works(int **fds, pid_t *pids, int i)
{
	close_fds(fds);
	wait_pids(pids, i);
	dup2(g_shell.stdin, STDIN_FILENO);
	dup2(g_shell.stdout, STDOUT_FILENO);
	i = 0;
	if (fds)
	{
		while (fds[i])
			free(fds[i++]);
		free(fds);
	}
}
