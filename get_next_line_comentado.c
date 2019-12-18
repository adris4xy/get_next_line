/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_comentado.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:47:48 by gmartin-          #+#    #+#             */
/*   Updated: 2019/12/18 14:41:15 by aortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

static void			ft_strdel(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int					ft_putline(int fd, char **s, char **line)
{
	int		size;
	char	*tmp;

	size = 0;
	while (s[fd][size] != '\n')									 //"size" va avanzando hasta encontrar la posicion del salto de linea,
		size++;													 //entonces se reserva memoria en "line" de la primera linea de s[fd],	
	*line = ft_substr(s[fd], 0, size);							 //y luego en "tmp" guarda el resto del texto(char static) desde
	tmp = ft_strdup(&s[fd][size + 1]);							 //la posicion siguiente al primer salto de linea, libera el
	free(s[fd]);												 // char estatico antiguo y lo que hay en "tmp" se lo ponemos a s[fd]
	s[fd] = tmp;												 // (char estatico actual), y retorna 1.
	return (1);
}

int					output(int ret, int fd, char **s, char **line)
{
	if (ret < 0)												 //En el caso de que lo leido tenga fallos, sea negativo returne error.
		return (-1);
	else if (ret == 0 && (s[fd] == NULL || s[fd][0] == '\0'))	 //Si ret es cero pero al estatico no se le ha llegado nada quiere
	{															 //decir que no se ha leido nada, y por tanto en "line" se reserva
		*line = ft_strdup("");									 //memoria de una cadena vacia.
		ft_strdel(&s[fd]);										 //Se libera y se pone a nulo el "char estatico".
		return (0);												 //Returna 0 porque significa que no hay mas que leer.
	}
	else if (ft_strchr(s[fd], '\n'))							 //Busca si hay un salto de linea, si lo hay returna a "ft_putline".
		return (ft_putline(fd, s, line));
	else
	{
		*line = ft_strdup(s[fd]);								 //Si no hay salto de linea, y esta todo correcto, significa que ha
		ft_strdel(&s[fd]);										 //llegado a su ultima linea, asi que reservamos memoria en "line"
		return (0);												 //de lo que queda del "char estatico" hasta el valor nulo, y se 
	}															 //libera y se pone a nulo el "char estatico" y se returna 0.
}

int					get_next_line(int fd, char **line)
{
	int				ret;
	static char		*s[4096];
	char			*buff;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL) 			 //Sirve para arreglar los fallos especificos.
		return (-1);
	if (!(buff = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1))) //Crea "buff" y le reserva una memoria de BUFFER_SIZE mas el
		return (-1);											 //del valor nulo siguiente.
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)				 //Lee los bytes de BUFFER_SIZE del file descriptor y los coge en el
																 //"buff" hasta que sea 0, si es 0 no entra en el bucle.
	{
		buff[ret] = '\0';										 //Ponemos a "buff" el valor nulo que le habiamos reservado antes.
		if (s[fd] == NULL)										 //Entra en el if si el static char esta vacio, y si entra
			s[fd] = ft_strdup(buff);							 //crea memoria con el tamaño de "buff" en ese momento.
		else
		{
			tmp = ft_strjoin(s[fd], buff);						 //Si en "buff" había algo entonces reservamos memoria en "tmp" para la
			free(s[fd]);										 //concatenacion entre el "char estatico" y el "buff", liberamos el
			s[fd] = tmp;										 //antiguo "char estatico" y metemos el "tmp" en el "char estatico".
		}
		if (ft_strchr(s[fd], '\n'))								 //Simplemente encuentra el primer salto de linea y rompe el bucle.
			break ;
	}
	free(buff);													 //Libera el "buff".
	return (output(ret, fd, s, line));							 //Te lleva hacia la funcion "output".
}
