#ifndef MINISHELL_H
# define MINISHELL_H


#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_minishell
{
	char	**env;
	int		stdin;
	int		stdout;
	int		status;
	int		*fd;
}				t_minishell;

typedef struct s_cmd
{
	int				f1;
	int				f2;
	int				pipe_in;
	int				pipe_out;
	int				redir_in;
	int				redir_out;
	char			**args;
	char			*limiter;
	t_minishell		*mshell;
	struct s_cmd	*next;
}				t_cmd;

typedef enum e_stat
{
	pipe_in = 1,
	pipe_out,
	redir_in_1,
	redir_in_2,
	redir_out_1,
	redir_out_2
}					t_stat;

int		exec(t_cmd *cmd_list);
void	init_env(t_minishell *mshell, char **envp);
char	*get_env(char *point, char **envp);
void	initialisation(t_minishell *mshell, char **envp);
void	work_here_doc(char *limiter, int f);

#endif