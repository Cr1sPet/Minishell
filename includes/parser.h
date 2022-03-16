#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char	**args;
	struct s_cmd	*next;
	struct s_redir *redr_list;
}				t_cmd;

typedef struct s_redir
{
	int		type_redr;
	char	*filename;
	struct s_redir	*next;
}				t_redir;

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

#endif