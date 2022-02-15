# include "minishell.h"

void parse(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			printf("%c\n", str[i]);
        if (str[i] == '\'')
			printf("%c\n", str[i]);
        if (str[i] == '$')
			printf("%c\n", str[i]);
        if (str[i] == '\\')
			printf("%c\n", str[i]);
		i++;
	}
}