/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:33:08 by mouerchi          #+#    #+#             */
/*   Updated: 2025/01/25 21:22:38 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibc.h"

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

static char	*gnl_append_and_free(char *stash, const char *buf)
{
	char	*new_stash;
	size_t	stash_len;
	size_t	buf_len;

	stash_len = 0;
	if (stash)
		stash_len = ft_strlen(stash);
	buf_len = 0;
	if (buf)
		buf_len = ft_strlen(buf);
	new_stash = (char *)malloc(sizeof(char) * (stash_len + buf_len + 1));
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	if (stash_len)
		ft_memcpy(new_stash, stash, stash_len);
	if (buf_len)
		ft_memcpy(new_stash + stash_len, buf, buf_len);
	new_stash[stash_len + buf_len] = '\0';
	free(stash);
	return (new_stash);
}

static char	*read_buffer(int fd, char *stash)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			if (stash)
				free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = gnl_append_and_free(stash, buffer);
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!*stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i += 1;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (stash[j] && j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*update_buffer(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i += 1;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	stash[fd] = read_buffer(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = update_buffer(stash[fd]);
	return (line);
}
