#include "get_next_line.h"

int	gnl_has_newline(char *stash)
{
	size_t	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_get_line(char *stash)
{
	size_t	len;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, len);
	line[len] = '\0';
	return (line);
}

char	*gnl_update_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_stash = ft_strdup(stash + i);
	free(stash);
	return (new_stash);
}

char	*gnl_read(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!gnl_has_newline(stash) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
			stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}
