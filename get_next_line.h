/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:56:46 by aortega-          #+#    #+#             */
/*   Updated: 2019/11/22 16:54:48 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define HAS_NEWLINE(str, split_at)    ((split_at = find_newline(str)) != -1)
# define HAS_NO_NEWLINE(str, split_at) ((split_at = find_newline(str)) == -1)

int		get_next_line(const int fd, char **line);
int		read_line(int fd, char **line, char *rest);
int		find_newline(char *str);
int		free_return(char **ptr, char **rest, int ret);
char	*ft_strappend(char *dest, char *src);
char	*ft_strncpy(char *dest, const char *src, int n);
int		ft_strlen(char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s);

#endif
