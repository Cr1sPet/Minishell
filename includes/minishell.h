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

char *get_cmd();    
char *parse(char *str, char **envp);
char *ft_dollar(char *str, int *i, char **envp);
int ft_pwd();
char *ft_quotes(char *str, int *i);
char *ft_quotes_2(char *str, int *i, char **envp);

#endif