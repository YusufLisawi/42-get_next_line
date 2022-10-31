/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:07:59 by yelaissa          #+#    #+#             */
/*   Updated: 2022/10/31 17:56:55 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// get the characters after \n
char	*store_next(char *store)
{
	int		i;
	int		j;
	char	*new_store;

	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	if (!store[i])
	{
		free(store);
		return (NULL);
	}
	new_store = (char *)malloc(sizeof(char) * (ft_strlen(store) - i + 1));
	if (!new_store)
		return (NULL);
	i++;
	j = 0;
	while (store[i])
		new_store[j++] = store[i++];
	new_store[j] = '\0';
	free(store);
	return (new_store);
}

char	*ft_getline(char *store)
{
	int		i;
	char	*line;

	i = 0;
	if (!store[i])
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (store[i] && store[i] != '\n')
	{
		line[i] = store[i];
		i++;
	}
	if (store[i] == '\n')
	{
		line[i] = store[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_and_store(int fd, char *store)
{
	char	buf[BUFFER_SIZE + 1];
	int		bytes_read;

	bytes_read = 1;
	while (ft_strchr(store, '\n') == NULL && bytes_read)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		buf[bytes_read] = '\0';
		store = ft_strjoin(store, buf);
	}
	return (store);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*store;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	store = read_and_store(fd, store);
	if (!store)
		return (NULL);
	line = ft_getline(store);
	store = store_next(store);
	return (line);
}
