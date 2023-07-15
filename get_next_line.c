/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:59:27 by fcosta-f          #+#    #+#             */
/*   Updated: 2023/07/15 15:45:51 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *backup)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (backup)
		buffer = backup;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		backup = malloc(sizeof(char) * BUFFER_SIZE);
		if (!backup)
			return (NULL);
		bytes_read = read(fd, backup, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		if (backup)
		{
			if (buffer)
				buffer = ft_strjoin(buffer, backup);
			else
				buffer = backup;
			free(backup);
			backup = NULL;
		}
	}
	return (buffer);
}

static char	*make_backup(char *backup, char *buffer)
{
	int		index;

	index = 0;
	if (ft_strchr(buffer, '\n'))
	{
		while (buffer[index] != '\n')
			index++;
	}
	backup = ft_substr(buffer, index, BUFFER_SIZE - index);
	return (backup);
}

char	*extract(char *buffer) //hacerlo por referencia o algo asi??s
{
	int	index;

	index = 0;
	while (buffer[index] != '\n')
		index++;
	buffer = ft_substr(buffer, 0, index);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	line = read_line(fd, backup);
	backup = make_backup(backup, line);
	line = extract(line);
	return (line);
}

// int main()
// {
// 	char *line;
// 	int fd = open("archivo.txt", O_RDONLY);  // Abre el archivo en modo lectura
//     if (fd < 0) {
//         printf("No se pudo abrir el archivo\n");
//         return 1;
//     }

//     // Leer y imprimir todas las líneas del archivo
//     //while ((line = get_next_line(fd)) != NULL) {
// 		line = get_next_line(fd);
//         printf("%s\n", line);
//         //free(line);  // Libera la memoria asignada a la línea
//    	//}

//     close(fd);  // Cierra el archivo
//     return 0;
// }




