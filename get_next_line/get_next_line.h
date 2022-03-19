/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:24:44 by jchopped          #+#    #+#             */
/*   Updated: 2022/01/08 15:20:33 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
int		get_next_line(char **ret, int fd);
// size_t	ft_strlen(char *str);
// char	*ft_strdup( char *str);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strchr( char *str, int ch);

#endif
