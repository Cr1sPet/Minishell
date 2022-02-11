#ifndef CRS_TERMCAP_H
# define  CRS_TERMCAP_H

# include "../../includes/minishell.h"
typedef	struct s_get_cmd
{
	int				balance;
	char			*cmd;
	char			*termtype;
	struct termios	tattr;
	struct termios	saved_tattr;
}				t_get_cmd;

int		ft_putint(int c);
char	*crs_strjoin(char *s1, char const *s2);

# endif