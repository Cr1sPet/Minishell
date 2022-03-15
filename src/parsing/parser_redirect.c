# include "minishell.h"

void left_redirect()
{
    printf("left redirect");
}

char *right_redirect(char *str, int *i)
{
    char    *file;
    char    *ret;
    
    ret = ft_substr(str, *i + 1, ft_strlen(str));
    file = ft_substr(str, 0, *i);
    printf("%s\n", file);
    return ret;
}