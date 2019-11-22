/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:09:48 by aortega-          #+#    #+#             */
/*   Updated: 2019/11/22 17:35:33 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	int			split_at;
	static char	rest[4096][BUFFER_SIZE + 1] = {{0}};

	if (fd < 0 || fd > 4096 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if ((*line = ft_strdup("")) == NULL)
		return (-1);
	if (rest[fd][0] == '\0')
		return (read_line(fd, line, rest[fd]));
	if (HAS_NEWLINE(rest[fd], split_at))
	{
		free(*line);
		if ((*line = (char*)malloc(sizeof(char) * (split_at + 1))) == NULL)
			return (-1);
		ft_strncpy(*line, rest[fd], split_at);
		(*line)[split_at] = '\0';
		ft_strcpy(rest[fd], rest[fd] + split_at + 1);
		return (1);
	}
	free(*line);
	if (!(*line = (char*)malloc(sizeof(char) * (ft_strlen(rest[fd]) + 1))))
		return (-1);
	ft_strcpy(*line, rest[fd]);
	rest[fd][0] = '\0';
	return (read_line(fd, line, rest[fd]));
}

int		read_line(int fd, char **line, char *rest)
{
	int		ret;
	int		split_at;
	char	*buf;

	if ((buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (free_return(line, NULL, -1));
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (HAS_NEWLINE(buf, split_at))
		{
			ft_strcpy(rest, buf + split_at + 1);
			buf[split_at] = '\0';
			if ((*line = ft_strappend(*line, buf)) == NULL)
				return (free_return(&buf, NULL, -1));
			return (free_return(&buf, NULL, 1));
		}
		if ((*line = ft_strappend(*line, buf)) == NULL)
			return (free_return(&buf, NULL, -1));
	}
	if (ret == -1)
		return (free_return(&buf, line, -1));
	return (free_return(&buf, NULL, ret));
}

int		find_newline(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

int		free_return(char **ptr, char **ptr2, int ret)
{
	if (ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (ptr2 != NULL)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	return (ret);
}
