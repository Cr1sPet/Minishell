#ifndef MINISHELL_H
# define MINISHELL_H


#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env_store
{
	char	*key;
	char	*val;
	int		equal;
}				t_env_store;

typedef struct s_minishell
{
	char			**env;
	int				stdin;
	int				stdout;
	int				status;
	int				fds[2];
	int				fds1[2];
	t_env_store		*env_store;
	t_env_store		*export;
	struct s_cmd	*cmd_list;
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
	default_pipe_in,
	default_pipe_out,
	pipe_in,
	pipe_out,
	default_redir_in,
	default_redir_out,
	redir_in_1,
	redir_in_2,
	redir_out_1,
	redir_out_2
}					t_stat;


void	export(char **args, t_minishell *mshell);
int		find_len(char **arr);
void	env(t_minishell *mshell);
void	pwd(t_minishell *mshell);
void	change_dir(t_minishell *mshell);
void	echo(char **args);
void	unset(char **args, t_minishell *mshell);
int		exec(t_cmd *cmd);
char	**cp_2d_arr(char **envp);
int		get_ind_env(char *point, char **envp);
void	memclean(char **s, size_t l);
char	*get_env(char *point, char **envp);
void	initialisation(t_minishell *mshell, char **envp);
void	work_here_doc(char *limiter, int f);

char	**collect_env (t_minishell *mshell);
void	print_env_store(t_env_store *env_store, t_minishell	*mshell);
char	*get_key(char *var);
int		parse_cmds(t_cmd *cmd);
int		ft_strcmp(char const *s1, char const *s2);
void	lst_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*lst_cmdnew(t_minishell *mshell);
t_cmd	*lst_cmdlast(t_cmd *lst);

#endif