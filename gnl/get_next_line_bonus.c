#include "get_next_line_bonus.h"

static t_fdlist	*find_fd(t_fdlist **fds, int fd)
{
	t_fdlist	*node;

	node = *fds;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = malloc(sizeof(t_fdlist));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->stash = NULL;
	node->next = *fds;
	*fds = node;
	return (node);
}

char	*gnl_extract_line(char *stash)
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

char	*gnl_update_stash(char *stash)
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

static int	read_to_stash(int fd, char **stash)
{
	char	*buffer;
	char	*joined;
	ssize_t	bytes;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = 1;
	while (!gnl_strchr(*stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			joined = gnl_strjoin(*stash, buffer, (size_t)bytes);
			if (!joined)
				bytes = -1;
			free(*stash);
			*stash = joined;
		}
	}
	free(buffer);
	if (bytes < 0)
		return (-1);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_fdlist	*fds;
	t_fdlist		*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = find_fd(&fds, fd);
	if (!node || read_to_stash(fd, &node->stash) < 0
		|| !node->stash || !*node->stash)
	{
		gnl_remove_fd(&fds, fd);
		return (NULL);
	}
	line = gnl_extract_line(node->stash);
	if (!line)
	{
		gnl_remove_fd(&fds, fd);
		return (NULL);
	}
	node->stash = gnl_update_stash(node->stash);
	return (line);
}
