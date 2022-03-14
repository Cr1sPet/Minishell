#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "../libft/libft.h"
#include "parser.h"

typedef struct s_minishell
{
	char	**env;
	int		stdin;
	int		stdout;
	int		status;
	int		fds[2];
	struct s_cmd *cmd_list;
}				t_minishell;

t_minishell shell;
#endif