#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char    **args;
}				t_cmd;

void	*parser(t_cmd *cmd, char *str, char **envp);
char	*ft_dollar(char *str, int *i, char **envp);
char	*ft_quotes(char *str, int *i);
char	*ft_quotes_2(char *str, int *i, char **envp);

#endif