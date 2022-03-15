#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	int		type_cmd;
	int		type_rd;
	char	*filename;
	char	**args;
	struct s_cmd	*next;
}				t_cmd;

void	*parser(char *str, char **envp);
char	*ft_dollar(char *str, int *i, char **envp);
char	*ft_quotes(char *str, int *i);
char	*ft_quotes_2(char *str, int *i, char **envp);
char	*ft_space(char *str, int i);
void	signal_init();
char 	*pipe_parse(int *i,char *str, char **envp);
char	**correct_str(char **str, char **envp);
int		prepars(const char *str);
t_cmd	*ft_lstnew_parse(void *content);
t_cmd	*ft_lstlast_parse(t_cmd *lst);
void	ft_lstadd_back_parse(t_cmd **lst, t_cmd *new);
char 	*right_redirect(char *str, int *i);
void 	left_redirect();

#endif