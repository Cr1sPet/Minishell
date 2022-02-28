# include "minishell.h"

int ft_pwd()
{
    char *pwd;

    pwd = malloc(sizeof(*pwd) * 2048);
    if (getcwd(pwd, 2048))
    {
        ft_putendl_fd(pwd, 1);
        free(pwd);
        return 1;
    }
    else
    {
        ft_putendl_fd("Error", 1);
        free(pwd);
        return 0;
    }
}