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

//crs
char *get_cmd();
//crs
char *parse(char *str, char **envp);
char *ft_dollar(char *str, int *i, char **envp);
int ft_pwd();

#endif