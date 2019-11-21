/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:09:48 by aortega-          #+#    #+#             */
/*   Updated: 2019/11/21 17:31:35 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strchr(const char *s, int c)
{
	int i;

	if ((char)c == '\0')
		return ((char*)s + ft_strlen(s));
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char*)s + i);
		i++;
	}
	return (NULL);
}

static int		ft_stock2line(char **stock, char **line)
{
	int len;

	if (ft_strchr(*stock, '\n') != NULL)
	{
		len = ft_strchr(*stock, '\n') - *stock;
		line[0] = ft_strsub(*stock, 0, len);
		*stock = ft_strchr(*stock, '\n') + 1;
		return (1);
	}
	line[0] = ft_strdup(*stock);
	*stock = NULL;
	return (0);
}

static int		read_f(char **line, const int fd, char **stock, char *str)
{
	char	*tmp;
	int		len;
	int		ret;

	while ((ret = read(fd, str, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (ret);
		str[ret] = '\0';
		tmp = ft_strdup(line[0]);
		free(line[0]);
		line[0] = ft_strjoin(tmp, str);
		free(tmp);
		if (ft_strchr(line[0], '\n'))
		{
			len = ft_strchr(line[0], '\n') - line[0];
			*stock = ft_strdup(ft_strchr(line[0], '\n') + 1);
			tmp = ft_strdup(line[0]);
			free(line[0]);
			line[0] = ft_strsub(tmp, 0, len);
			free(tmp);
			break ;
		}
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*stock = NULL;
	char		*str;

	if (line == NULL || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	line[0] = ft_strnew(BUFFER_SIZE);
	if (stock != NULL)
		if (ft_stock2line(&stock, &line[0]))
			return (1);
	str = ft_strnew(BUFFER_SIZE);
	if ((ret = read_f(&line[0], fd, &stock, str)) == -1)
		return (-1);
	free(str);
	if (ret == 0 && ft_strlen(line[0]) == 0)
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	int		ret;

	i = 0;
	(void)argc;
	fd = open((argv[1]), O_RDONLY);
	while (i < 3)
	{
		line = (char *)malloc(sizeof(*line) * 1);
		ret = get_next_line(fd, &line);
		printf("%d\n", ret);
		i++;
	}
}