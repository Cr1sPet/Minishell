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
	status = shell.status;
	if (pids)
	{
		while (i < nmb)
		{
			waitpid(pids[i], &status, 0);
			i++;
		}
		if (shell.status != status)
			shell.status = WEXITSTATUS(status);
		free(pids);
	}
}

void	cmd_end_works(int **fds, pid_t *pids, int i)
{
	// close (shell.fd_write);
	// close (shell.fd_read);
	close_fds(fds);
	wait_pids(pids, i);
	dup2(shell.stdin, STDIN_FILENO);
	dup2(shell.stdout, STDOUT_FILENO);
	i = 0;
	if (fds)
	{
		while (fds[i])
			free(fds[i++]);
		free(fds);
	}
}
