/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:59:27 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/07/17 20:24:04 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *backup, char *buf)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = 42;
	while (bytes_read > 0 && ft_strchr(backup, '\n') == NULL)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			return (backup);
		tmp = backup;
		backup = ft_strjoin(tmp, buf);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
	}
	return (backup);
}

static char	*make_backup(char *backup, char *buffer)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (buffer[start] != '\n')
		++start;
	start++;
	while (buffer[start + end] != '\0')
		++end;
	backup = ft_substr(buffer, start, end);
	return (backup);
}

char	*extract(char *buffer)
{
	int		index;
	char	*tmp;

	index = 0;
	tmp = buffer;
	while (buffer[index] != '\n')
		index++;
	buffer = ft_substr(buffer, 0, index + 1);
	free(tmp);
	tmp = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = read_line(fd, backup, buf);
	free(buf);
	buf = NULL;
	if (ft_strchr(line, '\n'))
	{
		backup = make_backup(backup, line);
		if (!backup)
		{
			free(backup);
			backup = NULL;
		}
		line = extract(line);
	}
	return (line);
}

 int main()
{
	char *line;
	int fd = open("41_no_nl", O_RDONLY);  // Abre el archivo en modo lectura
    if (fd < 0) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    // Leer y imprimir todas las líneas del archivo
    //while ((line = get_next_line(fd)) != NULL) {
		line = get_next_line(fd);
        printf("LINE1: %s\n", line);
		free(line);
		line = get_next_line(fd);
        printf("LINE2: %s\n", line);
		free(line);
		line = get_next_line(fd);
        printf("LINE3: %s\n", line);
    	free(line);  // Libera la memoria asignada a la línea
   	//}

    close(fd);  // Cierra el archivo
    return 0;
}
