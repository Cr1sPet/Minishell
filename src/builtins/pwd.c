# include "minishell.h"

int ft_pwd()
{
    char *pwd;

    pwd = malloc(sizeof(*pwd) * 2048);
    if (getcwd(pwd, 2048))
    {
        printf("%s\n", pwd);
        free(pwd);
        return 1;
    }
    else
    {
        printf("Error\n");
        free(pwd);
        return 0;
    }
}