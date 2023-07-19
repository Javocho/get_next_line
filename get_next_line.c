/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:59:27 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/07/19 20:59:51 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_buffer(char *buffer)
{
	free(buffer);
	buffer = NULL;
	return (NULL);
}

static char	*read_line(int fd, char *backup)
{
	char	*buf;
	int		bytes_read;

	bytes_read = 42;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
	{
		if (backup)
			return (free_buffer(backup));
		return (NULL);
	}
	while (bytes_read > 0 && ft_strchr(backup, '\n') == NULL)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (backup)
				free_buffer(backup);
			return (free_buffer(buf));
		}
		if (bytes_read == 0 && !backup)
			return (free_buffer(buf));
		buf[bytes_read] = '\0';
		backup = ft_strjoin(backup, buf);
	}
	free_buffer(buf);
	return (backup);
}

static char	*make_backup(char *backup)
{
	int		start;
	int		end;
	char	*tmp;

	start = 0;
	end = 0;
	while (backup[start] && backup[start] != '\n')
		++start;
	if (!backup[start])
		return (free_buffer(backup));
	tmp = malloc(sizeof(char) * (ft_strlen(backup) - start + 1));
	if (!tmp)
		return (free_buffer(backup));
	++start;
	while (backup[start + end] != '\0')
	{
		tmp[end] = backup[start + end];
		++end;
	}
	tmp[end] = '\0';
	free_buffer(backup);
	return (tmp);
}

static char	*extract_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (backup[0] == '\0')
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\0')
		line = malloc(sizeof(char) * (i + 1));
	else
		line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!backup || (backup && !ft_strchr(backup, '\n')))
		backup = read_line(fd, backup);
	if (!backup)
		return (NULL);
	line = extract_line(backup);
	if (!line)
		return (free_buffer(backup));
	backup = make_backup(backup);
	return (line);
}

//  int main()
// {
// 	char *line;
// 	int fd = open("multiple_nl.txt", O_RDONLY);  // Abre el archivo en modo lectura

//     // Leer y imprimi	r todas las líneas del archivo
//     //while ((line = get_next_line(fd)) != NULL) {
// 		line = get_next_line(fd);
//         printf("LINE1: %s", line);
// 		free(line);
// 		line = get_next_line(fd);
//         printf("LINE2: %s", line);
// 		free(line);
// 		line = get_next_line(fd);
//         printf("LINE3: %s", line);
//     	free(line);  // Libera la memoria asignada a la línea
//    	//}

//     close(fd);  // Cierra el archivo
//     return 0;
// }
