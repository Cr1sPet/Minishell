#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"

//crs
char *get_cmd();
//crs
char *parse(char *str, char **envp);
char *ft_dollar(char *str, int *i, char **envp);

#endif