#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
	{
		l++;
	}
	return (l);
}

char	*ft_strdup( char *str)
{
	size_t	len;
	size_t	i;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	new_str = (char *) malloc ((len + 1) * sizeof(char));
	if ((void *) 0 == new_str)
		return ((void *)0);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	*ft_strjoin(char *s1, char *s2)
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
	return (new_s);
}

char	*ft_strchr( char *str, int ch)
{
	int	i;

	if (NULL == str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == (char)ch)
		return ((char *)(str + i));
	return ((void *)0);
}
