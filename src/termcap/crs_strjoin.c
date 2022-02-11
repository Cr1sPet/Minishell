#include "minishell.h"

char	*crs_strjoin(char *s1, char const *s2)
{
	char	*new_s;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!(s1 && s2))
		return ((void *) 0);
	size = sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1);
	new_s = (char *) malloc(size);
	if ((void *)0 == new_s)
		return ((void *)0);
	i = 0;
	j = 0;
	while (s1[i])
		new_s[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new_s[j++] = s2[i++];
	new_s[j] = 0;
	free (s1);
	return (new_s);
}
