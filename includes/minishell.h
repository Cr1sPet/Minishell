#ifndef MINISHELL_H
# define MINISHELL_H

# include <wait.h>
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
	int				env_changed;
	t_env_store		*env_store;
	t_env_store		*export;
	struct s_cmd	*cmd_list;
}				t_minishell;


//typedef struct s_cmd
//{
//	int				f1;
//	int				f2;
//	int				pipe_in;
//	int				pipe_out;
//	int				redir_in;
//	int				redir_out;
//	char			**args;
//	char			*limiter;
//	t_minishell		*mshell;
//	struct s_cmd	*next;
//}				t_cmd;

typedef enum e_stat
{
	default_pipe_in,
	default_pipe_out,
	pipe_in,
	pipe_out,
	redir_in_1,
	redir_in_2,
	redir_out_1,
	redir_out_2
}					t_stat;

typedef struct s_redir
{
	int					type_redr;
	char				*filename;
	struct s_redir		*next;
}				t_redir;

typedef struct s_cmd
{
	char			**args;
	int				pipe_in;
	int				pipe_out;
	t_redir			*redir_in;
	t_redir			*redir_out;
	t_minishell		*mshell;
	struct s_cmd	*next;
}				t_cmd;



void	add_env_store(t_env_store *temp, char *flag);
void	add_val_by_index (t_env_store *env_store, char *val, int index);
// int		if_key_exists (t_env_store *env_store, t_env_store *elem, int len);
int		get_shlvl(void);
t_env_store	*add_elem_by_index (t_env_store *env_store, t_env_store *elem, int index, int len);
int		len_env_store(t_env_store *env_store);
void	add_elem_to_env_store (t_env_store **env_store, t_env_store *elem);
int		set_redir_in(t_redir *redir);
int		set_redir_out(t_redir *redir);
void	*parser(char *str, char **envp);
char	*ft_dollar(char *str, int *i, char **envp);
char	*ft_quotes(char *str, int *i);
char	*ft_quotes_2(char *str, int *i, char **envp);
// char	*ft_space(char *str, int i);
void	signal_init();
char 	*pipe_parse(int *i,char *str, char **envp);
char	**correct_str(char **str, char **envp);
int		prepars(const char *str);
t_cmd	*ft_lstnew_parse(void *content);
t_cmd	*ft_lstlast_parse(t_cmd *lst);
t_redir	*ft_lstlast_redir(t_redir *lst);
t_redir	*ft_lstnew_redir(void *content, int type);
void	ft_lstadd_back_parse(t_cmd **lst, t_cmd *new);
void	ft_lstadd_back_redir(t_redir **lst, t_redir *new);
char 	*right_redirect(char *str, int *i, char **envp);
char *left_redirect(char *str, int *i, char **envp);
void redir(char *str, char **envp);

t_redir	*lst_redirlast(t_redir *lst);
void	lst_rediradd_back(t_redir **redir, t_redir *new);
t_redir	*lst_redirnew(char *file, int type);

void	export();
int		len_2d_str(char **str);
void	env(void);
void	pwd();
void	change_dir();
void	echo(char **args);
void	unset(char **args, char **env);
int		exec();
char	**cp_2d_arr(char **envp);
int		get_ind_env(char *point, char **envp);
void	memclean(char **s, size_t l);
char	*get_env(char *point, char **envp);
void	initialisation(char **envp);
void	work_here_doc(char *limiter, int f);

char	**collect_env(t_minishell *mshell);
void	print_env_store(t_env_store *env_store);
char	*get_key(char *var);
int		parse_cmds(t_cmd *cmd);
int		ft_strcmp(char const *s1, char const *s2);
void	lst_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*lst_cmdnew(t_minishell *mshell);
t_cmd	*lst_cmdlast(t_cmd *lst);
t_minishell	shell;
#endif