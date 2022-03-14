#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char    *cmd[3];
	char	**args;
	struct s_cmd	*next;
}				t_cmd;

void	*parser(t_cmd *cmd, char *str, char **envp);
char	*ft_dollar(char *str, int *i, char **envp);
char	*ft_quotes(char *str, int *i);
char	*ft_quotes_2(char *str, int *i, char **envp);
char	*ft_space(char *str, int i);
void	signal_init();
char 	*pipe_parse(int i,char *str, char **envp);
char	*correct_str(char *str, char **envp);
int		prepars(const char *str);

#endif