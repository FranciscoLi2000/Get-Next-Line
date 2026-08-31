#include "get_next_line.h"

static char	*extract_line(char *stash)
{
	size_t	len;
	char	*line;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	gnl_memcpy(line, stash, len);
	line[len] = '\0';
	return (line);
}

static char	*update_stash(char *stash)
{
	char	*newline;
	char	*rest;
	size_t	rest_len;

	newline = gnl_strchr(stash, '\n');
	if (!newline)
	{
		free(stash);
		return (NULL);
	}
	rest_len = gnl_strlen(newline + 1);
	rest = malloc(rest_len + 1);
	if (!rest)
	{
		free(stash);
		return (NULL);
	}
	gnl_memcpy(rest, newline + 1, rest_len + 1);
	free(stash);
	return (rest);
}

static int	append_read(int fd, char **stash, char *buffer)
{
	ssize_t	bytes;
	char	*joined;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
		return (0);
	joined = gnl_strjoin(*stash, buffer, (size_t)bytes);
	if (!joined)
		return (-1);
	free(*stash);
	*stash = joined;
	return (1);
}

static int	read_to_stash(int fd, char **stash)
{
	char	*buffer;
	int		status;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	status = 1;
	while (!gnl_strchr(*stash, '\n') && status > 0)
		status = append_read(fd, stash, buffer);
	free(buffer);
	return (status);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_to_stash(fd, &stash) < 0 || !stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash);
	return (line);
}
