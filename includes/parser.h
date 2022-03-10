#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char    **args;
}				t_cmd;

char *parser(t_cmd pars_cmd,char *str, char **envp);
char *ft_dollar(char *str, int *i, char **envp);
int ft_pwd();
char *ft_quotes(char *str, int *i);
char *ft_quotes_2(char *str, int *i, char **envp);

#endif